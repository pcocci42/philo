/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:58:09 by pcocci            #+#    #+#             */
/*   Updated: 2023/03/06 14:20:10 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int get_time(struct timeval start)
{
    struct timeval stop;
    
    gettimeofday(&stop, NULL);
    return (((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);
    
}

void    *check_death(void *arg)
{
    t_info  *info;
    int     i;

    info = (t_info *)arg;
    while (!info->death)
    {   
        i = -1;
        while (++i < info->number_of_philosophers)
        {
            if (info->philo->last_meal + info->time_to_die < get_time(info->tv))
            {
                info->death++;
                if(info->death == 1 && info->philo[i].meals != -1)
                    printf("%dms %d has died\n", get_time(info->tv), i + 1);
            }
        }
    }
    /* i = -1;
    while (++i < info->number_of_philosophers)
    {
        pthread_detach(info->philo[i].philosophers);
    } */
    return (NULL);
}

void    *routine(void *arg)
{   
    t_philo *philo;
    philo = (t_philo *)arg;
    
    while (!philo->info->death && philo->meals--)
    {
    if(philo->info->death == 0)
        printf("%dms %d is thinking\n", get_time(philo->info->tv),philo->nome);
    pthread_mutex_lock(&philo->forkr);
    if(philo->info->death == 0)
        printf("%dms %d has taken a fork right\n", get_time(philo->info->tv), philo->nome);
    pthread_mutex_lock(philo->forkl);
    if(philo->info->death == 0)
        printf("%dms %d has taken a fork left\n", get_time(philo->info->tv), philo->nome);
    philo->last_meal = get_time(philo->info->tv);
    if(philo->info->death == 0)
        printf("%dms %d is eating\n", get_time(philo->info->tv), philo->nome);
    usleep(philo->info->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->forkr);
    pthread_mutex_unlock(philo->forkl);
    if(philo->info->death == 0)
        printf("%dms %d is sleeping\n", get_time(philo->info->tv), philo->nome);
    usleep(philo->info->time_to_sleep * 1000);
    }
    return(NULL);
}


void    new_philos(t_info *info)
{
    int	i;

	pthread_create(&info->ghost_reaper, 0, &check_death, info);
	i = 0;
	while (i < info->number_of_philosophers)
	{
		pthread_create(&info->philo[i].philosophers, 0, &routine, info->philo + i);
		i += 2;
		usleep(1);
	}
	i = 1;
	while (i < info->number_of_philosophers)
	{
		pthread_create(&info->philo[i].philosophers, 0, &routine, info->philo + i);
		i += 2;
		usleep(1);
	}
	pthread_join(info->ghost_reaper, 0);
	i = -1;
	while (++i < info->number_of_philosophers)
		pthread_join(info->philo[i].philosophers, 0);
	free(info->philo);
}

void    data(t_info * info)
{
    int i;

    i = -1;
    while (++i < info->number_of_philosophers)
    {
        pthread_mutex_init(&info->philo[i].forkr, NULL);
        if (i == info->number_of_philosophers - 1)
            info->philo[i].forkl = &info->philo[0].forkr;
        else
            info->philo[i].forkl = &info->philo[i + 1].forkr;
        info->philo[i].last_meal = 0;
        info->philo[i].info = info;
        info->philo[i].nome = i + 1;
        info->philo[i].meals = info->number_of_times_each_philosopher_must_eat;
    }
}

int main(int ac, char **av)
{   
    t_info          info;

    gettimeofday(&info.tv, NULL);
    info.philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (ac == 5 || ac == 6)
    {   
        info.number_of_philosophers = ft_atoi(av[1]);
        info.time_to_die = ft_atoi(av[2]);
        info.time_to_eat = ft_atoi(av[3]);
        info.time_to_sleep = ft_atoi(av[4]);
        info.death = 0;
        if (ac == 6)
            info.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
        else 
            info.number_of_times_each_philosopher_must_eat = -1;
        data(&info);
        new_philos(&info);
    }
    return (0);
}