/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 19:06:31 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosophize(void *param)
{
	t_philo	*philo;
	char	i;

	philo = (t_philo *)param;
	if (philo->nbr_philos == 1)
		return (NULL);
	i = 0;
	while (!*philo->someone_died && is_hungry(philo))
	{
		if (i % 4 == 0)
			take_forks(philo);
		else if (i % 4 == 1)
			eat(philo);
		else if (i % 4 == 2)
			philo_sleep(philo);
		else if (i % 4 == 3)
			think(philo);
		i++;
	}
	if (philo->has_forks)
		unlock_forks(philo);
	return (NULL);
}

static void	*die(t_philo *philo)
{
	*(philo->someone_died) = true;
	pthread_mutex_lock(philo->print);
	print_action(philo, DIED);
	pthread_mutex_unlock(philo->print);
	return (NULL);
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	i = 0;
	while (1)
	{
		if (!is_alive(&table->philos[i]))
		{
			die(&table->philos[i]);
			break ;
		}
		if (!someone_is_hungry(table))
			break ;
		if (++i == table->nbr_philos)
			i = 0;
	}
	return (NULL);
}
