/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/15 11:27:21 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sim(t_data	*dt, pthread_t *t, pthread_mutex_t *fk)
{
	int	i;

	i = 0;
	while (i < dt->num_philo)
	{
		if (pthread_join(t[i], NULL) != 0)
			return ;
		i++;
	}
	destroy_mutexes(dt, fk);
	free(t);
	free_data(dt, dt->num_philo);
}

int	exit_sim(pthread_t *t, pthread_t p, t_data *data)
{
	if (pthread_join(p, NULL) != 0)
		return (0);
	destroy_sim(data, t, data->forks);
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
		data->fk[i] = 0;
		i++;
	}
	data->philos[i] = NULL;
	return (data);
}

t_data	*init(int num_p, int meals, char **argv)
{
	t_data			*data;

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
	data->fk = malloc(sizeof(int) * num_p);
	if (!data->fk)
		return (NULL);
	data = init_philos(data, num_p);
	data->forks = malloc(sizeof(pthread_mutex_t) * num_p);
	if (!data->forks)
		return (NULL);
	init_mutexes(data);
	return (data);
}
