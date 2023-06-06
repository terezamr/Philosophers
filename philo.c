/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/06 15:20:20 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		print_status(philo, DEAD);
		return (1);
	}
	return (0);
}

void	eating(t_philo *philo)
{
	int	i;
	int	*forks;

	i = philo->id;
	forks = get_index_f(philo);
	pthread_mutex_lock(&philo->data->forks[forks[0]]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->data->forks[forks[1]]);
	print_status(philo, FORK);
	print_status(philo, EATING);
	philo->last_meal = get_time();
	sleep_time(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[forks[0]]);
	pthread_mutex_unlock(&philo->data->forks[forks[1]]);
	free(forks);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	sleep_time(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo, THINKING);
	sleep_time(50);
}

void	*philo(void *philo)
{
	void	*a;
	t_philo	*philo_cp;

	a = NULL;
	philo_cp = (t_philo *)philo;
	if (philo_cp->id % 2 != 0)
		thinking(philo_cp);
	while (check_death(philo) == 0)
	{
		eating(philo_cp);
		if (check_death(philo) == 1)
			return (NULL);
		sleeping(philo_cp);
		if (check_death(philo) == 1)
			return (NULL);
		thinking(philo_cp);
	}
	return (a);
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		*t;
	t_data			*data;
	int				num_p;

	i = 0;
	(void)argc;
	if (argc != 5)
		return (1);
	num_p = ft_atoi(argv[1]);
	t = malloc(sizeof(pthread_t) * num_p);
	data = init(num_p, argv);
	while (i < num_p)
	{
		if (pthread_create(&t[i], NULL, &philo, data->philos[i]) != 0)
			return (exit_sim(num_p, t, data));
		i++;
	}
	i = 0;
	destroy_sim(num_p, t, data->forks);
	free(t);
	free_data(data, num_p);
	return (EXIT_SUCCESS);
}
