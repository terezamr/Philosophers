/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/06 11:50:34 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	ini;
	int	number;
	int	sig;

	ini = 0;
	number = 0;
	sig = 1;
	while ((nptr[ini] >= 9 && nptr[ini] <= 13) || nptr[ini] == 32)
		ini++;
	if (nptr[ini] == '-' || nptr[ini] == '+')
	{
		if (nptr[ini] == '-')
			sig = -1;
		ini++;
	}
	while (nptr[ini] >= 48 && nptr[ini] <= 57)
	{
		number = number * 10 + (nptr[ini] - 48);
		ini++;
	}
	return (sig * number);
}

void	free_data(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(data->philos[i]);
		i++;
	}
	free(data->philos);
	free(data->forks);
	free(data);
}

int	*get_index_f(t_philo *philo)
{
	int	*forks;

	forks = malloc(sizeof(int) * 2);
	if (philo->id % 2 != 0)
	{
		forks[0] = philo->id - 1;
		if (philo->id == philo->data->num_philo)
			forks[1] = 0;
		else
			forks[1] = philo->id;
	}
	else
	{
		forks[1] = philo->id - 1;
		if (philo->id == philo->data->num_philo)
			forks[0] = 0;
		else
			forks[0] = philo->id;
	}
	return (forks);
}
