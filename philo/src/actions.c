/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 12:01:17 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	take_forks_else(t_philo *philo)
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
	print_normal(philo);
	print_normal(philo);
	pthread_mutex_unlock(philo->print);
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
		print_normal(philo);
		print_normal(philo);
		pthread_mutex_unlock(philo->print);
	}
	else
		take_forks_else(philo);
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
	print_negative(philo);
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
	print_faint(philo);
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
	print_italic(philo);
	pthread_mutex_unlock(philo->print);
}
