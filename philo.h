/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:57:26 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/29 15:40:06 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int     id;
    t_data  *data;
}   t_philo;

typedef struct s_data
{
	struct timeval  time;
    int             time_to_eat;
    t_philo			**philos;
}   t_data;

int 	ft_atoi(const char *nptr);
void    free_data(t_data *data, int num);

#endif