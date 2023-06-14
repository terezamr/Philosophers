/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/12 15:27:39 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	int	*forks;

	forks = get_index_f(philo);
	while (philo->data->fk[forks[0]] == 1)
		if (philo->data->dead == 1)
			return ;
	pthread_mutex_lock(&philo->data->forks[forks[0]]);
	philo->data->fk[forks[0]] = 1;
	print_status(philo, FORK);
	while (philo->data->fk[forks[1]] == 1)
		if (philo->data->dead == 1)
			return ;
	pthread_mutex_lock(&philo->data->forks[forks[1]]);
	philo->data->fk[forks[1]] = 1;
	if (philo->data->dead == 1)
		return ;
	print_status(philo, FORK);
	print_status(philo, EATING);
	if (philo->data->max_meals != -1)
	{
		pthread_mutex_lock(&philo->number);
		philo->meal_number = philo->meal_number + 1;
		pthread_mutex_unlock(&philo->number);
	}
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal);
	sleep_time(philo->data->time_to_eat);
	philo->data->fk[forks[0]] = 0;
	philo->data->fk[forks[1]] = 0;
	pthread_mutex_unlock(&philo->data->forks[forks[0]]);
	pthread_mutex_unlock(&philo->data->forks[forks[1]]);
	free(forks);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	sleep_time(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo, THINKING);
	sleep_time(2);
}
