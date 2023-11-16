/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:51 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 15:18:58 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		kill(table->philos[i].pid, SIGKILL);
	}
	sem_close(table->death);
	sem_close(table->print);
	sem_close(table->stop);
	sem_close(table->forks);
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("forks");
}

void	close_some(sem_t *a, sem_t *b, sem_t *c, sem_t *d)
{
	if (a != SEM_FAILED)
		sem_close(a);
	if (b != SEM_FAILED)
		sem_close(b);
	if (c != SEM_FAILED)
		sem_close(c);
	if (d != SEM_FAILED)
		sem_close(d);
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("forks");
}
