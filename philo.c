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

int get_time(t_data *data)
{
    struct timeval  newTime;
    long            time;
    long            remain;

    if (gettimeofday(&newTime, NULL) != 0)
    {
        perror("gettimeofday");
        return (1);
    }
    time = (newTime.tv_sec - data->time.tv_sec) * 1000 +
                        (newTime.tv_usec - data->time.tv_usec) / 1000;
    remain = data->time_to_eat - time;
    if (remain > 0)
        usleep(remain * 1000);
    return (time);
}

void    *philo(void *philo)
{
    void    *a;
    int     i;
    t_philo  *philo_cpy;

    a = NULL;
    philo_cpy = (t_philo*)philo;
    i = philo_cpy->id;
    printf("hello %d\n", i);
    printf("%d is eating\n", i);
    get_time(philo_cpy->data);
    printf("%d is not eating\n", i);
    return (a);
}

t_data  *init(int num_p, char **argv)
{
    t_data          *data;
    int             i;
    struct timeval  currentTime;

    i = 0;
    data = malloc(sizeof(t_data));
    if (gettimeofday(&currentTime, NULL) == 0)
        data->time = currentTime;
    else
    {
        perror("gettimeofday");
        return NULL;
    }
    data->time_to_eat = ft_atoi(argv[2]);
    data->philos = malloc(sizeof(t_philo) * num_p + 1);
    while (i < num_p)
    {
        data->philos[i] = malloc(sizeof(t_philo) * 1);
        data->philos[i]->id = i;
        data->philos[i]->data = data;
        i++;
    }
    data->philos[i] = '\0';
    return (data);
}

int main(int argc, char **argv)
{
    int             i;
    pthread_t       t[2];
    t_data          *data;
    int             num_p;

    i = 0;
    (void)argc;
    if (argc != 3)
        return (1);
    num_p = ft_atoi(argv[1]);
    data = init(num_p, argv);
    while (i < num_p)
    {
        if (pthread_create(&t[i], NULL, &philo, data->philos[i]) != 0)
            return (0);
        i++;
    }
    i = 0;
    while (i < num_p)
    {
        if (pthread_join(t[i], NULL) != 0)
            return (0);
        printf("goodbye thread %d\n", i);
        i++;
    }
    free_data(data, num_p);
}
