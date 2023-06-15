/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/15 11:24:24 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->life);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&data->philos[i]->meal);
		pthread_mutex_destroy(&data->philos[i]->number);
		i++;
	}
}

void	init_mutexes(t_data *data)
{
	int	i;
	int	num;

	i = 0;
	num = data->num_philo;
	while (i < num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i]->meal, NULL);
		pthread_mutex_init(&data->philos[i]->number, NULL);
		i++;
	}
	pthread_mutex_init(&data->life, NULL);
}