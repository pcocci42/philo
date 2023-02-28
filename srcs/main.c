/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:58:09 by pcocci            #+#    #+#             */
/*   Updated: 2023/02/28 11:33:11 by pcocci           ###   ########.fr       */
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
    t_philo *philo;
    philo = (t_philo *)arg;
    //pthread_mutex_lock(&(info->philo->forks[]));
    printf("Hi i'm %d\n", philo->nome);
    //pthread_mutex_unlock(&(info->philo->forks[info->i]));
    return(arg);
}


void    new_philos(t_info info)
{
    int         i;
    int         j;
    int         nb;

    nb = info.number_of_philosophers;
    i = 0;
    j = 0;
    while (i < nb)
    {   
        info.philo[i].nome = i + 1;
        if (pthread_create(&info.philo[i].philosophers, NULL, &routine, &info.philo[i]) != 0)
            printf("error");
        usleep(1);
        i += 2;
    }
    i = 1;
    while (i < nb)
    {
        info.philo[i].nome = i + 1;
        if (pthread_create(&info.philo[i].philosophers, NULL, &routine, &info.philo[i]) != 0)
            printf("error");
        usleep(1);
        i += 2;
    }
    while (j < nb)
    {   
        if (pthread_join(info.philo[j].philosophers, NULL) != 0)
            printf("error");
        j++;
    }
}

int main(int ac, char **av)
{   
    t_info          info;
    int i = 0;
    info.philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (ac == 5 || ac == 6)
    {   
        gettimeofday(&info.tv, NULL);
        info.number_of_philosophers = ft_atoi(av[1]);
        /* info.philo->philosophers = malloc(sizeof(pthread_t) * info.number_of_philosophers);
        info.philo->forks = malloc(sizeof(pthread_mutex_t) * info.number_of_philosophers); */
        
        while (i < info.number_of_philosophers)
        {
            pthread_mutex_init(&info.philo[i].forks, NULL);
            i++;
        }
        i = 0;
        while (i < info.number_of_philosophers)
        {
            info.philo[i].info = &info;
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
            pthread_mutex_destroy(&info.philo[i].forks);
            i++;
        }

    }
    return (0);
}