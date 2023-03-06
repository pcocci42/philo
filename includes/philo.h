/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:58:13 by pcocci            #+#    #+#             */
/*   Updated: 2023/03/06 13:45:26 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo {

    int             nome;
    pthread_t       philosophers;
    pthread_mutex_t forkr;
    pthread_mutex_t *forkl;
    struct s_info    *info;
    int             last_meal;
    int             meals;
}   t_philo;

typedef struct s_info {

    t_philo         *philo;
    pthread_t       ghost_reaper;
    int             number_of_philosophers; 
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_times_each_philosopher_must_eat;
    struct timeval  tv;
    int             death;

}   t_info;

int     ft_atoi(const char *str);

#endif