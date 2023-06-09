/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/22 14:21:00 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->life);
	if (philo->data->dead == 1 || philo->data->full == 1)
	{
		pthread_mutex_unlock(&philo->data->life);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->life);
	return (0);
}

void	*routines_loop(t_philo *philo)
{
	while (1)
	{
		if (check_condition(philo) == 1)
			return (NULL);
		if (eating(philo) == 1)
			continue ;
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
	}
}

void	*philo(void *philo)
{
	t_philo	*philo_cp;

	philo_cp = (t_philo *)philo;
	if (philo_cp->data->num_philo == 1)
	{
		print_status(philo, FORK);
		sleep_time(philo_cp->data->time_to_die);
		return (NULL);
	}
	if (philo_cp->id % 2 != 0)
		sleep_time(30);
	return (routines_loop(philo_cp));
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

	i = 0;
	data = init(argc, argv);
	if (!data)
		return (EXIT_FAILURE);
	t = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (!t)
		return (EXIT_FAILURE);
	if (pthread_create(&p, NULL, &police, data) != 0)
		return (exit_sim(NULL, p, data));
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&t[i], NULL, &philo, data->philos[i]) != 0)
			return (exit_sim(t, p, data));
		i++;
	}
	if (pthread_join(p, NULL) != 0)
		return (exit_sim(t, p, data));
	destroy_sim(data, t, data->forks);
	return (EXIT_SUCCESS);
}
