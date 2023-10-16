/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/10/16 14:04:38 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
 
void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->index + 1 < philo->nbr_philos)
	{
		pthread_mutex_lock(philo->print);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		if (*(philo->stop))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->print);
			return ;
		}
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->index + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->index + 1);
		pthread_mutex_unlock(philo->print);
	}
	else
	{
		pthread_mutex_lock(philo->print);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		if (*(philo->stop))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->print);
			return ;
		}
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->index + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->index + 1);
		pthread_mutex_unlock(philo->print);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (*philo->stop)
	{
		pthread_mutex_unlock(philo->print);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	printf("%ld %d is eating\n", \
		ft_time() - philo->start_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
	philo->last_meal = ft_time();
	philo->nbr_meals++;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (*philo->stop)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	printf("%ld %d is sleeping\n", \
		ft_time() - philo->start_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (*philo->stop)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	printf("%ld %d is thinking\n", \
		ft_time() - philo->start_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
}
