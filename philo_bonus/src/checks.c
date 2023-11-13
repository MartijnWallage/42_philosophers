/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:35:37 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/13 19:37:20 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(t_philo *philo)
{
	bool	ret;

	ret = ft_time() - philo->last_meal <= philo->table->time_to_die;
	return (ret);
}

bool	is_hungry(t_philo *philo)
{
	bool	ret;

	if (philo->table->max_meals == -1)
		return (true);
	ret = philo->nbr_meals < philo->table->max_meals;
	return (ret);
}

bool	is_last_meal(t_philo *philo)
{
	bool	ret;
	
	ret = (philo->nbr_meals + 1 == philo->table->max_meals);
	return (ret);
}

bool	is_last_philo(t_philo *philo)
{
	if (philo->index == philo->table->nbr_philos - 1)
		return (true);
	return (false);
}
