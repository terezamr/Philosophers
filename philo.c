/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/12 15:26:02 by mvicente         ###   ########.fr       */
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
		eating(philo_cp);
		if (philo_cp->data->dead == 1)
			return (NULL);
		sleeping(philo_cp);
		if (philo_cp->data->dead == 1)
			return (NULL);
		thinking(philo_cp);
		if (philo_cp->data->dead == 1)
			return (NULL);
	}
	return (a);
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
	int				num_p;

	i = 0;
	(void)argc;
	if (argc != 5)
		return (1);
	num_p = ft_atoi(argv[1]);
	t = malloc(sizeof(pthread_t) * num_p);
	data = init(num_p, argv);
	if (pthread_create(&p, NULL, &police, data) != 0)
		return (exit_sim(NULL, p, data));
	while (i < num_p)
	{
		if (pthread_create(&t[i], NULL, &philo, data->philos[i]) != 0)
			return (exit_sim(t, p, data));
		i++;
	}
	i = 0;
	destroy_sim(data, t, p, data->forks);
	return (EXIT_SUCCESS);
}
