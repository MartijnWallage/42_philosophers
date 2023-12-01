/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/15 23:08:25 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosophize(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->table->nbr_philos == 1 || philo->table->max_meals == 0)
		return (NULL);
	while (!is_stop(philo->table))
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
	}
	if (philo->has_forks)
		unlock_forks(philo);
	return (NULL);
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;
	int		sated_philos;

	table = (t_table *)param;
	sated_philos = 0;
	i = 0;
	while (sated_philos < table->nbr_philos && is_alive(&table->philos[i]))
	{
		if (is_hungry(&table->philos[i]))
			sated_philos = 0;
		else
			sated_philos++;
		if (++i == table->nbr_philos)
			i = 0;
	}
	stop(table);
	return (NULL);
}
