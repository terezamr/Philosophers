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

int	get_time2(t_data *data)
{
	struct timeval	newtime;
	long			time;

	if (gettimeofday(&newtime, NULL) != 0)
	{
		perror("gettimeofday");
		return (1);
	}
	time = (newtime.tv_sec - data->time.tv_sec) * 1000
		+ (newtime.tv_usec - data->time.tv_usec) / 1000;
	return (time);
}

time_t	get_time(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_time(int time_to_sleep)
{
	struct timeval	newtime;
	long			time;
	long			stop;

	if (gettimeofday(&newtime, NULL) != 0)
	{
		perror("gettimeofday");
		return ;
	}
	time = (newtime.tv_sec * 1000) + (newtime.tv_usec / 1000);
	stop = time + time_to_sleep;
	while (get_time() < stop)
		usleep(100);
}

void	eat(t_philo *philo)
{
	int	f1;
	int	f2;
	int	i;

	i = philo->id;
	if (philo->id % 2 != 0)
	{
		f1 = philo->id - 1;
		if (philo->id == philo->data->num_philo)
			f2 = 0;
		else
			f2 = philo->id;
	}
	else
	{
		f2 = philo->id - 1;
		if (philo->id == philo->data->num_philo)
			f1 = 0;
		else
			f1 = philo->id;
	}
	pthread_mutex_lock(&philo->data->forks[f1]);
	printf("%ld %d has taken a fork %d\n", get_time(), i, f1 + 1);
	pthread_mutex_lock(&philo->data->forks[f2]);
	printf("%ld %d has taken a fork %d\n", get_time(), i, f2 + 1);
	printf("%ld %d is eating\n", get_time(), philo->id);
	sleep_time(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[f1]);
	pthread_mutex_unlock(&philo->data->forks[f2]);
	printf("%ld %d is sleeping\n", get_time(), philo->id);
	sleep_time(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	//int	time_to_think;

	//time_to_think = philo->data->time_to_eat;
	printf("%ld %d is thinking\n", get_time(), philo->id);
	sleep_time(1000);
}

void	*philo(void *philo)
{
	void	*a;
	t_philo *philo_cp;

	a = NULL;
	philo_cp = (t_philo *)philo;
	if (philo_cp->id % 2 != 0)
		think(philo_cp);
	while (1)
	{
		eat(philo_cp);
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
