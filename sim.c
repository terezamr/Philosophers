/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/12 15:12:09 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sim(t_data	*data, pthread_t *t, pthread_t p, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (pthread_join(p, NULL) != 0)
		return ;
	while (i < data->num_philo)
	{
		if (pthread_join(t[i], NULL) != 0)
			return ;
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&data->life);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&data->philos[i]->meal);
		pthread_mutex_destroy(&data->philos[i]->number);
		i++;
	}
	free(t);
	free_data(data, data->num_philo);
}

int	exit_sim(pthread_t *t, pthread_t p, t_data *data)
{
	destroy_sim(data, t, p, data->forks);
	return (EXIT_FAILURE);
}

t_data	*init_philos(t_data *data, int num_p)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * num_p + 1);
	if (!data->philos)
		return (NULL);
	while (i < num_p)
	{
		data->philos[i] = malloc(sizeof(t_philo) * 1);
		data->philos[i]->id = i + 1;
		data->philos[i]->data = data;
		data->philos[i]->last_meal = data->start_time;
		data->philos[i]->meal_number = 0;
		i++;
	}
	data->philos[i] = NULL;
	return (data);
}

t_data	*init(int num_p, int meals, char **argv)
{
	t_data			*data;
	int				i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = get_time();
	data->num_philo = num_p;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->max_meals = meals;
	data->dead = 0;
	data->full = 0;
	data = init_philos(data, num_p);
	data->forks = malloc(sizeof(pthread_mutex_t) * num_p);
	if (!data->forks)
		return (NULL);
	i = 0;
	while (i < num_p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i]->meal, NULL);
		pthread_mutex_init(&data->philos[i]->number, NULL);
		i++;
	}
	pthread_mutex_init(&data->life, NULL);
	return (data);
}
