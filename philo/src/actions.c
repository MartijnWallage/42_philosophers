/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 18:19:44 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	take_forks_else(t_philo *philo)
{
	if (*philo->someone_died)
		return ;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	philo->has_forks = true;
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		unlock_forks(philo);
		return ;
	}
	print_action(philo, FORK);
	print_action(philo, FORK);
	pthread_mutex_unlock(philo->print);
}

void	take_forks(t_philo *philo)
{
	if (*philo->someone_died)
		return ;
	if (philo->nbr_philos == 1)
	{
		while (!*philo->someone_died)
			;
		return ;
	}
	if (!*philo->someone_died && philo->index % 2 == 0 && !is_last_philo(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		philo->has_forks = true;
		pthread_mutex_lock(philo->print);
		if (*philo->someone_died)
		{
			pthread_mutex_unlock(philo->print);
			unlock_forks(philo);
			return ;
		}
		print_action(philo, FORK);
		print_action(philo, FORK);
		pthread_mutex_unlock(philo->print);
	}
	else if (!*philo->someone_died)
		take_forks_else(philo);
}

void	eat(t_philo *philo)
{
	if (*philo->someone_died)
		return ;
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_action(philo, EAT);
	pthread_mutex_unlock(philo->print);
	philo->last_meal = ft_time();
	philo->nbr_meals++;
	ft_usleep(philo->time_to_eat);
	unlock_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (*philo->someone_died)
		return ;
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_action(philo, SLEEP);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (*philo->someone_died)
		return ;
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_action(philo, THINK);
	pthread_mutex_unlock(philo->print);
}
