/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:51:08 by mwallage          #+#    #+#             */
/*   Updated: 2023/10/14 16:58:15 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define FORMAT	"Format:\n\t./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef struct s_philo
{
	int	index;
	int	last_meal;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	nbr_meals;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}		t_philo;

typedef struct s_arg
{
	int	nbr_philos;
	time_t	start_time;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_meals;
}		t_arg;

#endif
