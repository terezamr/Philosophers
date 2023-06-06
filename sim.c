/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/06 14:47:02 by mvicente         ###   ########.fr       */
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
		i++;
	}
	i = 0;
	while (i < num_p)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	exit_sim(int num_p, pthread_t *t, t_data *data)
{
	destroy_sim(num_p, t, data->forks);
	free(t);
	free_data(data, num_p);
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
		i++;
	}
	data->philos[i] = NULL;
	return (data);
}

t_data	*init(int num_p, char **argv)
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
	data = init_philos(data, num_p);
	data->forks = malloc(sizeof(pthread_mutex_t) * num_p);
	if (!data->forks)
		return (NULL);
	i = 0;
	while (i < num_p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (data);
}
