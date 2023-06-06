/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/06 11:56:46 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep(t_philo *philo)
{
	int	i;
	int	*forks;

	i = philo->id;
	forks = get_index_f(philo);
	pthread_mutex_lock(&philo->data->forks[forks[0]]);
	printf("%ld %d has taken a fork %d\n", get_time(), i, forks[0] + 1);
	pthread_mutex_lock(&philo->data->forks[forks[1]]);
	printf("%ld %d has taken a fork %d\n", get_time(), i, forks[1] + 1);
	printf("%ld %d is eating\n", get_time(), philo->id);
	sleep_time(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[forks[0]]);
	pthread_mutex_unlock(&philo->data->forks[forks[1]]);
	printf("%ld %d is sleeping\n", get_time(), philo->id);
	sleep_time(philo->data->time_to_sleep);
	free(forks);
}

void	think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time(), philo->id);
	sleep_time(1000);
}

void	*philo(void *philo)
{
	void	*a;
	t_philo	*philo_cp;

	a = NULL;
	philo_cp = (t_philo *)philo;
	if (philo_cp->id % 2 != 0)
		think(philo_cp);
	while (1)
	{
		eat_sleep(philo_cp);
		think(philo_cp);
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
	if (argc != 4)
		return (1);
	num_p = ft_atoi(argv[1]);
	t = malloc(sizeof(pthread_t) * num_p);
	data = init(num_p, argv);
	while (i < num_p)
	{
		if (pthread_create(&t[i], NULL, &philo, data->philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	destroy_sim(num_p, t, data->forks);
	free(t);
	free_data(data, num_p);
}
