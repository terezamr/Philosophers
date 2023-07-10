/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/22 14:30:04 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_meal(t_philo *philo)
{
	if (philo->data->max_meals != -1)
	{
		pthread_mutex_lock(&philo->number);
		philo->meal_number = philo->meal_number + 1;
		pthread_mutex_unlock(&philo->number);
	}
}

int	eating(t_philo *philo)
{
	int	*forks;

	forks = get_index_f(philo);
	if (!forks)
		return (1);
	if (locking_forks(philo, forks) == 1)
	{
		free(forks);
		return (1);
	}
	if (philo->data->dead == 1)
	{
		unlock_fork(philo, forks);
		return (1);
	}
	meal_time(philo);
	unlock_fork(philo, forks);
	free(forks);
	increase_meal(philo);
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
	unsigned long int	time;
	unsigned long int	ttt;

	time = get_time() - philo->last_meal;
	ttt = time / 2;
	if (ttt + time > (unsigned long int)philo->data->time_to_die)
		ttt = 1;
	print_status(philo, THINKING);
	usleep(ttt * 1000);
	if (check_condition(philo) == 1)
		return (1);
	return (0);
}
