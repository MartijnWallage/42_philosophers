/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:35:37 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 18:44:44 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(t_philo *philo)
{
	return (ft_time() - philo->last_meal <= (long)philo->time_to_die);
}

bool	is_hungry(t_philo *philo)
{
	if (philo->max_meals == -1)
		return (true);
	return (philo->nbr_meals < philo->max_meals);
}

bool	someone_is_hungry(t_table *table)
{
	int	i;

	if (table->max_meals == -1)
		return (true);
	i = -1;
	while (++i < table->nbr_philos)
		if (table->philos[i].nbr_meals < table->max_meals)
			return (true);
	return (false);
}

bool	is_last_philo(t_philo *philo)
{
	if (philo->index == philo->nbr_philos - 1)
		return (true);
	return (false);
}
