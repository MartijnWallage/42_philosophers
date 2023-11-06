/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/06 20:51:49 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosophize(void *param)
{
	t_philo	*philo;
	char	i;

	philo = (t_philo *)param;
	if (philo->table->nbr_philos == 1)
		return (NULL);
	i = 0;
	while (is_hungry(philo))
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->someone_died)
		{
			pthread_mutex_unlock(&philo->table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
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

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	i = 0;
	while (is_alive(&table->philos[i]) && someone_is_hungry(table))
	{
		if (++i == table->nbr_philos)
			i = 0;
	}
	return (NULL);
}
