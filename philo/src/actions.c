/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 18:53:12 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(philo->print);
 	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	} 
	print_action(philo, FORK);
	print_action(philo, FORK);
	pthread_mutex_unlock(philo->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_action(philo, EAT);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_time();
	philo->nbr_meals++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	unlock_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
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
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_action(philo, THINK);
	pthread_mutex_unlock(philo->print);
}
