/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:57:26 by mvicente          #+#    #+#             */
/*   Updated: 2023/06/20 12:36:17 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define FORK 5

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	meal;
	time_t			last_meal;
	pthread_mutex_t	number;
	int				meal_number;
	t_data			*data;
}		t_philo;

typedef struct s_data
{
	time_t			start_time;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	t_philo			**philos;
	int				*fk;
	pthread_mutex_t	*forks;
	pthread_mutex_t	life;
	int				dead;
	int				full;
}	t_data;

/*Simulation*/
void	destroy_sim(t_data	*dt, pthread_t *t, pthread_mutex_t *fk);
int		exit_sim(pthread_t *t, pthread_t p, t_data *data);
int		validator(int argc, char **argv);
t_data	*init(int num_p, int argc, char **argv);

/*Mutexes*/
void	destroy_mutexes(t_data *data, pthread_mutex_t *forks);
void	init_mutexes(t_data *data);

/*Routines*/
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

/*Time*/
time_t	get_time(void);
void	sleep_time(int time_to_sleep);
int		check_death(t_philo *philo);
int		check_all_max_meals(t_data *data);

/*Aux*/
int		ft_atoi(const char *nptr);
void	free_data(t_data *data, int num);
int		*get_index_f(t_philo *philo);
void	print_status(t_philo *philo, int action);
int		check_numbers(char **argv);

#endif