/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/15 15:44:15 by mvicente         ###   ########.fr       */
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
		if (data->philos[i])
			free(data->philos[i]);
		i++;
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->fk)
		free(data->fk);
	if (data)
		free(data);
}

int	*get_index_f(t_philo *philo)
{
	int	*forks;

	forks = malloc(sizeof(int) * 2);
	if (!forks)
		return (NULL);
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

void	print_status(t_philo *philo, int action)
{
	time_t	time;

	time = get_time() - philo->data->start_time;
	if (action == 1)
		printf("%ld %d is eating\n", time, philo->id);
	if (action == 2)
		printf("%ld %d is sleeping\n", time, philo->id);
	if (action == 3)
		printf("%ld %d is thinking\n", time, philo->id);
	if (action == 4)
		printf("%ld %d died\n", time, philo->id);
	if (action == 5)
		printf("%ld %d has taken a fork\n", time, philo->id);
}

int	validator(int argc, char **argv)
{
	int	meals;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		meals = ft_atoi(argv[5]);
		if (meals <= 0)
			return (EXIT_FAILURE);
	}
	else
		meals = -1;
	return (meals);
}
