/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:57:26 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/06 15:01:36 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define FORK 5

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	time_t	last_meal;
	t_data	*data;
}		t_philo;

typedef struct s_data
{
	time_t			start_time;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			**philos;
	pthread_mutex_t	*forks;
}	t_data;

/*Time*/
time_t	get_time(void);
void	sleep_time(int time_to_sleep);

/*Simulation*/
t_data	*init(int num_p, char **argv);
void	destroy_sim(int num_p, pthread_t *t, pthread_mutex_t *forks);
int		exit_sim(int num_p, pthread_t *t, t_data *data);

/*Aux*/
int		ft_atoi(const char *nptr);
void	free_data(t_data *data, int num);
int		*get_index_f(t_philo *philo);
void	print_status(t_philo *philo, int action);

#endif