/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/15 12:28:39 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->life);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->life);
		print_status(philo, DEAD);
		pthread_mutex_unlock(&philo->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal);
	return (0);
}

int	check_max_meals(t_philo	*philo)
{
	pthread_mutex_lock(&philo->number);
	if (philo->meal_number == philo->data->max_meals)
	{
		pthread_mutex_unlock(&philo->number);
		return (1);
	}
	pthread_mutex_unlock(&philo->number);
	return (0);
}

void	*philo(void *philo)
{
	void	*a;
	t_philo	*philo_cp;

	a = NULL;
	philo_cp = (t_philo *)philo;
	if (philo_cp->id % 2 != 0)
	{
		thinking(philo_cp);
		sleep_time(30);
	}
	while (1)
	{
		if (philo_cp->data->dead == 1 || philo_cp->data->full == 1)
			return (NULL);
		eating(philo_cp);
		if (philo_cp->data->dead == 1 || philo_cp->data->full == 1)
			return (NULL);
		sleeping(philo_cp);
		if (philo_cp->data->dead == 1 || philo_cp->data->full == 1)
			return (NULL);
		thinking(philo_cp);
		if (philo_cp->data->dead == 1 || philo_cp->data->full == 1)
			return (NULL);
	}
	return (a);
}

int	check_all_max_meals(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->num_philo)
	{
		if (check_max_meals(data->philos[i]) == 1)
			full = full + 1;
		else
			return (1);
		i++;
	}
	if (full == data->num_philo)
	{
		data->full = 1;
		return (0);
	}
	return (1);
}

void	*police(void *data)
{
	int		i;
	void	*a;
	t_data	*data_cp;

	a = NULL;
	data_cp = (t_data *)data;
	while (1)
	{
		i = 0;
		if (check_all_max_meals(data_cp) == 0)
			return (a);
		while (i < data_cp->num_philo)
		{
			if (check_death(data_cp->philos[i]) == 1)
				return (a);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		*t;
	pthread_t		p;
	t_data			*data;
	int				meals;

	i = 0;
	meals = validator(argc, argv);
	if (meals == EXIT_FAILURE)
		return (EXIT_FAILURE);
	t = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	data = init(ft_atoi(argv[1]), meals, argv);
	if (pthread_create(&p, NULL, &police, data) != 0)
		return (exit_sim(NULL, p, data));
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&t[i], NULL, &philo, data->philos[i]) != 0)
			return (exit_sim(t, p, data));
		i++;
	}
	if (pthread_join(p, NULL) != 0)
		return (EXIT_FAILURE);
	destroy_sim(data, t, data->forks);
	return (EXIT_SUCCESS);
}
