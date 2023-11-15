/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/15 22:47:49 by mwallage         ###   ########.fr       */
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
		if (!is_someone_hungry(philo))
		{
			print_action(philo, EAT);
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
	int	meal_time;

	philo = (t_philo *)param;
	pthread_create(&philo->monitor, NULL, monitor, philo);
	pthread_detach(philo->monitor);
	meal_time = mealtime(which_round(philo), philo->table);
	ft_usleep(meal_time / 2);
 	if (is_last_philo(philo))
		ft_usleep(DELAY);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}
