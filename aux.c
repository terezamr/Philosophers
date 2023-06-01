/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/29 15:38:25 by mvicente         ###   ########.fr       */
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

void    free_data(t_data *data, int num)
{
    int i;

    i = 0;
    while (i < num)
    {
        free(data->philos[i]);
        i++;
    }
    free(data->philos);
    free(data);
}