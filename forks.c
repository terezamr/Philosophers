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

void	unlock_fork(t_philo *philo, int *forks)
{
	pthread_mutex_unlock(&philo->data->forks[forks[0]]);
	pthread_mutex_unlock(&philo->data->forks[forks[1]]);
	pthread_mutex_lock(&philo->data->searching[forks[0]]);
	pthread_mutex_lock(&philo->data->searching[forks[1]]);
	philo->data->fk[forks[0]] = 0;
	philo->data->fk[forks[1]] = 0;
	pthread_mutex_unlock(&philo->data->searching[forks[0]]);
	pthread_mutex_unlock(&philo->data->searching[forks[1]]);
}

int	locking_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->data->forks[forks[0]]);
	print_status(philo, FORK);
	philo->data->fk[forks[0]] = 1;
	pthread_mutex_lock(&philo->data->forks[forks[1]]);
	print_status(philo, FORK);
	philo->data->fk[forks[1]] = 1;
	return (0);
}
