/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 20:39:15 by mwallage         ###   ########.fr       */
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

void	dream(t_philo *philo)
{
	int	meal_time;
	int	round;

	round = which_round(philo);
	meal_time = mealtime(round, philo->table);
	ft_usleep(meal_time - current_time(philo) - 1);
	if (is_last_philo(philo) && philo->nbr_meals + 1 == philo->table->max_meals)
		ft_usleep(8);
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
