/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/02 17:05:16 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sim(int num_p, pthread_t *t, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < num_p)
	{
		if (pthread_join(t[i], NULL) != 0)
			return ;
		printf("goodbye thread %d\n", i);
		i++;
	}
	i = 0;
	while (i < num_p)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

t_data	*init(int num_p, char **argv)
{
	t_data			*data;
	int				i;
	struct timeval	currenttime;

	i = 0;
	data = malloc(sizeof(t_data));
	if (gettimeofday(&currenttime, NULL) == 0)
		data->time = currenttime;
	else
	{
		perror("gettimeofday");
		return (NULL);
	}
    data->start_time = get_time();
	data->num_philo = num_p;
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	data->philos = malloc(sizeof(t_philo) * num_p + 1);
	while (i < num_p)
	{
		data->philos[i] = malloc(sizeof(t_philo) * 1);
		data->philos[i]->id = i + 1;
		data->philos[i]->data = data;
		i++;
	}
	data->philos[i] = NULL;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_p);
	i = 0;
	while (i < num_p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (data);
}
