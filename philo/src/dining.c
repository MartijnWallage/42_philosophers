/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/07 14:20:49 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosophize(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->table->nbr_philos == 1 || philo->table->max_meals == 0)
		return (NULL);
	while (true)
	{
		if (someone_died(philo->table))
			break ;
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		if (!is_hungry(philo))
			break;
		think(philo);
	}
	if (philo->has_forks)
		unlock_forks(philo);
	return (NULL);
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	i = 0;
	while (is_alive(&table->philos[i]))
	{
		if (++i == table->nbr_philos)
		{
			if (!someone_is_hungry(table))
				return (NULL);
			i = 0;
		}
	}
	return (NULL);
}
