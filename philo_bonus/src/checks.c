/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:35:37 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/13 20:50:29 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->meal_lock);
	ret = ft_time() - philo->last_meal <= philo->table->time_to_die;
	pthread_mutex_unlock(&philo->meal_lock);
	return (ret);
}

bool	is_hungry(t_philo *philo)
{
	bool	ret;

	if (philo->table->max_meals == -1)
		return (true);
	pthread_mutex_lock(&philo->meal_lock);
	ret = philo->nbr_meals < philo->table->max_meals;
	pthread_mutex_unlock(&philo->meal_lock);
	return (ret);
}

bool	is_last_meal(t_philo *philo)
{
	bool	ret;
	
	pthread_mutex_lock(&philo->meal_lock);
	ret = (philo->nbr_meals + 1 == philo->table->max_meals);
	pthread_mutex_unlock(&philo->meal_lock);
	return (ret);
}

bool	is_last_philo(t_philo *philo)
{
	if (philo->index == philo->table->nbr_philos - 1)
		return (true);
	return (false);
}
