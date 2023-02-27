/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:58:09 by pcocci            #+#    #+#             */
/*   Updated: 2023/02/27 16:40:44 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int get_time(t_info tv)
{
    int time;
    struct timeval tv2;

    time = tv.tv.tv_sec * 1000000 + tv.tv.tv_usec;
    return ((tv2.tv_sec * 1000000 + tv2.tv_usec - time)/ 1000);
}

void    *routine(void *arg)
{   
    t_info *info;
    info = (t_info *)arg;
    info->i++;
    pthread_mutex_lock(&(info->philo->forks[info->i]));
    printf("Hi i'm %d\n", info->philo->nome[info->i]);
    pthread_mutex_unlock(&(info->philo->forks[info->i]));
    return(info);
}


void    new_philos(t_info info)
{
    int         i;
    int         j;
    int         nb;

    nb = info.number_of_philosophers;
    i = 1;
    j = 0;
    while (i < nb)
    {   
        info.philo->nome[i] = i + 1;
        if (pthread_create(&info.philo->philosophers[i], NULL, &routine, &info) != 0)
            printf("error");
        usleep(1);
        i += 2;
    }
    i = 0;
    while (i < nb)
    {
        info.philo->nome[i] = i + 1;
        if (pthread_create(&info.philo->philosophers[i], NULL, &routine, &info) != 0)
            printf("error");
        usleep(1);
        i += 2;
    }
    while (j < nb)
    {   
        if (pthread_join(info.philo->philosophers[j], NULL) != 0)
            printf("error");
        j++;
    }
}

int main(int ac, char **av)
{   
    t_info          info;
    int i = 0;
    info.philo = malloc(sizeof(t_info) * ft_atoi(av[1]));
    info.i = 0;
    if (ac == 5 || ac == 6)
    {   
        gettimeofday(&info.tv, NULL);
        info.number_of_philosophers = ft_atoi(av[1]);
        info.philo->philosophers = malloc(sizeof(pthread_t) * info.number_of_philosophers);
        info.philo->nome = malloc(sizeof(int) * info.number_of_philosophers);
        info.philo->forks = malloc(sizeof(pthread_mutex_t) * info.number_of_philosophers);
        while (i < info.number_of_philosophers)
        {
            pthread_mutex_init(&info.philo->forks[i], NULL);
            i++;
        }
        info.time_to_die = ft_atoi(av[2]);
        info.time_to_eat = ft_atoi(av[3]);
        info.time_to_sleep = ft_atoi(av[4]);
        if (ac == 6)
            info.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);

        new_philos(info);
        i = 0;
        while (i < info.number_of_philosophers)
        {
            printf("%d\n", info.philo->nome[i]);
            i++;
        }
        i = 0;
        while (i < info.number_of_philosophers)
        {
            pthread_mutex_destroy(&info.philo->forks[i]);
            i++;
        }

    }
    return (0);
}