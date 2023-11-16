/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 22:26:24 by mwallage         ###   ########.fr       */
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
			exit(0);
		}
		if (!is_someone_hungry(philo))
		{
			print_action(philo, EAT);
			exit(0);
		}
		sem_post(philo->table->death);
	}
	return (NULL);
}

void	*philosophize(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_create(&philo->monitor, NULL, monitor, philo);
	pthread_detach(philo->monitor);
	dream(philo);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}
