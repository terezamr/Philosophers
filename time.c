/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/15 14:23:33 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->life);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->life);
		print_status(philo, DEAD);
		pthread_mutex_unlock(&philo->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal);
	return (0);
}

int	check_max_meals(t_philo	*philo)
{
	pthread_mutex_lock(&philo->number);
	if (philo->meal_number == philo->data->max_meals)
	{
		pthread_mutex_unlock(&philo->number);
		return (1);
	}
	pthread_mutex_unlock(&philo->number);
	return (0);
}

int	check_all_max_meals(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->num_philo)
	{
		if (check_max_meals(data->philos[i]) == 1)
			full = full + 1;
		else
			return (1);
		i++;
	}
	if (full == data->num_philo)
	{
		data->full = 1;
		return (0);
	}
	return (1);
}
