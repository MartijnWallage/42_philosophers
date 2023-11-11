/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:51 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/11 17:01:54 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	end_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
		kill(table->philos[i].pid, SIGKILL);
	sem_close(table->death);
	sem_close(table->print);
	sem_close(table->stop);
	sem_close(table->forks);
}

void	free_all(t_table *table)
{
	free(table->philos);
}
