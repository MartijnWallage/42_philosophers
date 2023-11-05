/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:51 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 19:09:23 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	end_threads(t_table *table)
{
	int	i;

	pthread_join(table->monitor, NULL);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philos[i].thread, NULL);
}

void	end_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print);
}

void	free_all(t_table *table)
{
	free(table->philos);
	free(table->forks);
}
