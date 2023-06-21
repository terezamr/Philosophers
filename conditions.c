/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/21 09:47:51 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_lock(&data->life);
		data->full = 1;
		pthread_mutex_unlock(&data->life);
		return (0);
	}
	return (1);
}

int	check_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->life);
	if (philo->data->dead == 1 || philo->data->full == 1)
	{
		pthread_mutex_unlock(&philo->data->life);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->life);
	return (0);
}
