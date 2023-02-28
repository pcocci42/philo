/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:58:09 by pcocci            #+#    #+#             */
/*   Updated: 2023/02/28 14:21:52 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int get_time(struct timeval start)
{
    struct timeval stop;
    
    gettimeofday(&stop, NULL);
    return (((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);
    
}

void    *routine(void *arg)
{   
    t_philo *philo;
    philo = (t_philo *)arg;
    int     forkr;
    int     forkl; 

    while (1)
    {
    printf("%dms %d is thinking\n", get_time(philo->info->tv),philo->nome);
    pthread_mutex_lock(&philo->forkr);
    printf("%dms %d has taken a fork right\n", get_time(philo->info->tv), philo->nome);
    pthread_mutex_lock(philo->forkl);
    printf("%dms %d has taken a fork left\n", get_time(philo->info->tv), philo->nome);
    philo->last_meal = get_time(philo->info->tv);
    printf("%dms %d is eating\n", get_time(philo->info->tv), philo->nome);
    usleep(philo->info->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->forkr);
    pthread_mutex_unlock(philo->forkl);
    printf("%dms %d is sleeping\n", get_time(philo->info->tv), philo->nome);
    usleep(philo->info->time_to_sleep * 1000);

    }
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
    gettimeofday(&info.tv, NULL);
    info.philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (ac == 5 || ac == 6)
    {   
        info.number_of_philosophers = ft_atoi(av[1]);
        while (i < info.number_of_philosophers)
        {
            pthread_mutex_init(&info.philo[i].forkr, NULL);
            if (i == info.number_of_philosophers - 1)
                info.philo[i].forkl = &info.philo[0].forkr;
            else
                info.philo[i].forkl = &info.philo[i + 1].forkr;
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
        /* while (i < info.number_of_philosophers)
        {
            pthread_mutex_destroy(&info.forks[i]);
            i++;
        } */

    }
    return (0);
}