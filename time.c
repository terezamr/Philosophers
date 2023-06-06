/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:38:24 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/06 11:39:36 by mvicente         ###   ########.fr       */
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
