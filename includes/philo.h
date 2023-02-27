/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:58:13 by pcocci            #+#    #+#             */
/*   Updated: 2023/02/27 16:39:39 by pcocci           ###   ########.fr       */
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

    int             *nome;
    pthread_t       *philosophers;
    pthread_mutex_t *forks;
    
}   t_philo;

typedef struct s_info {

    t_philo *philo;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int last_meal;
    int i;
    struct  timeval tv;

}   t_info;

int     ft_atoi(const char *str);

#endif