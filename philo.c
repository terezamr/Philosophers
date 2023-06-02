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
#include <pthread.h>

int	get_time(t_data *data)
{
	struct timeval	newtime;
	long			time;
	long			remain;

	if (gettimeofday(&newtime, NULL) != 0)
	{
		perror("gettimeofday");
		return (1);
	}
	time = (newtime.tv_sec - data->time.tv_sec) * 1000
		+ (newtime.tv_usec - data->time.tv_usec) / 1000;
	remain = data->time_to_eat - time;
	if (remain > 0)
	{
		printf("is eating\n");
		usleep(remain * 1000);
	}
	return (time);
}

void	*philo(void *philo)
{
	void			*a;
	int				i;
	t_philo			*philo_cpy;
	int				f1;
	int				f2;

	a = NULL;
	philo_cpy = (t_philo *)philo;
	i = philo_cpy->id;
	printf("hello %d\n", i);
	f1 = philo_cpy->id;
	if (philo_cpy->id == (philo_cpy->data->num_philo - 1))
		f2 = 0;
	else
		f2 = philo_cpy->id + 1;
	pthread_mutex_lock(&philo_cpy->data->forks[f1]);
	printf("%d has fork 1\n", i);
	pthread_mutex_lock(&philo_cpy->data->forks[f2]);
	printf("%d has fork 2\n", i);
	get_time(philo_cpy->data);
	pthread_mutex_unlock(&philo_cpy->data->forks[f1]);
	pthread_mutex_unlock(&philo_cpy->data->forks[f2]);
	return (a);
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
	data->num_philo = num_p;
	data->time_to_eat = ft_atoi(argv[2]);
	data->philos = malloc(sizeof(t_philo) * num_p + 1);
	while (i < num_p)
	{
		data->philos[i] = malloc(sizeof(t_philo) * 1);
		data->philos[i]->id = i;
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

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		*t;
	t_data			*data;
	int				num_p;

	i = 0;
	(void)argc;
	if (argc != 3)
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
