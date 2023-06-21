/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/21 11:27:46 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->life);
	pthread_mutex_destroy(&data->printing);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&data->philos[i]->meal);
		pthread_mutex_destroy(&data->philos[i]->number);
		pthread_mutex_destroy(&data->searching[i]);
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
		pthread_mutex_init(&data->searching[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->life, NULL);
	pthread_mutex_init(&data->printing, NULL);
}
