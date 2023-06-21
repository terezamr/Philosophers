/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/21 11:29:52 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_fork(t_philo *philo, int *forks, int index)
{
	// while (philo->data->fk[forks[index]] == 1)
	// {
	// 	pthread_mutex_lock(&philo->data->life);
	// 	if (philo->data->dead == 1)
	// 	{
	// 		pthread_mutex_unlock(&philo->data->life);
	// 		return (1);
	// 	}
	// 	pthread_mutex_unlock(&philo->data->life);
	// }
	pthread_mutex_lock(&philo->data->searching[forks[index]]);
	if (philo->data->fk[forks[index]] == 1)
	{
		pthread_mutex_lock(&philo->data->life);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->life);
			pthread_mutex_unlock(&philo->data->searching[forks[index]]);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->life);
		pthread_mutex_unlock(&philo->data->searching[forks[index]]);
		return (-2);
	}
	pthread_mutex_lock(&philo->data->forks[forks[index]]);
	print_status(philo, FORK);
	philo->data->fk[forks[index]] = 1;
	pthread_mutex_unlock(&philo->data->searching[forks[index]]);
	return (0);
}

void	unlock_fork(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->data->searching[forks[0]]);
	pthread_mutex_lock(&philo->data->searching[forks[1]]);
	philo->data->fk[forks[0]] = 0;
	philo->data->fk[forks[1]] = 0;
	pthread_mutex_unlock(&philo->data->searching[forks[0]]);
	pthread_mutex_unlock(&philo->data->searching[forks[1]]);
	pthread_mutex_unlock(&philo->data->forks[forks[0]]);
	pthread_mutex_unlock(&philo->data->forks[forks[1]]);
}

int	eating(t_philo *philo)
{
	int	*forks;
	int	value;

	forks = get_index_f(philo);
	if (!forks)
		return (1);
	value = lock_fork(philo, forks, 0);
	if (value == 1 || value == -2)
		return (value);
	value = lock_fork(philo, forks, 1);
	if (value == 1)
		return (value);
	else if (value == -2)
	{
		philo->data->fk[forks[0]] = 0;
		pthread_mutex_unlock(&philo->data->forks[forks[0]]);
		return (-2);
	}
	pthread_mutex_lock(&philo->meal);
	print_status(philo, EATING);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal);
	sleep_time(philo->data->time_to_eat);
	if (philo->data->max_meals != -1)
	{
		pthread_mutex_lock(&philo->number);
		philo->meal_number = philo->meal_number + 1;
		pthread_mutex_unlock(&philo->number);
	}
	unlock_fork(philo, forks);
	free(forks);
	if (check_condition(philo) == 1)
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	sleep_time(philo->data->time_to_sleep);
	if (check_condition(philo) == 1)
		return (1);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_status(philo, THINKING);
	sleep_time(2);
	if (check_condition(philo) == 1)
		return (1);
	return (0);
}
