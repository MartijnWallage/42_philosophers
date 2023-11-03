/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/03 17:25:46 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
 
bool	is_last_philo(t_philo *philo)
{
	if (philo->index == philo->nbr_philos - 1)
		return (true);
	return (false);
}

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0 && !is_last_philo(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print);
		if (*(philo->someone_died))
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
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print);
		if (*(philo->someone_died))
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
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		if (philo->index % 2 == 0 && !is_last_philo(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		pthread_mutex_unlock(philo->print);
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
	if (*philo->someone_died)
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
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	printf("%ld %d is thinking\n", \
		ft_time() - philo->start_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
}
