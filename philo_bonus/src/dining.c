/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/13 19:32:58 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->table->death);
		if (!is_alive(philo))
		{
			print_action(philo, DIED);
			sem_post(philo->table->stop);
			break ;
		}
		if (is_last_philo(philo) && !is_hungry(philo))
		{
			sem_post(philo->table->stop);
			break ;
		}
		sem_post(philo->table->death);
	}
	return (NULL);
}

void	*philosophize(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->table->nbr_philos == 1 || philo->table->max_meals == 0)
		return (NULL);
	pthread_create(&philo->monitor, NULL, monitor, philo);
	pthread_detach(philo->monitor);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}
