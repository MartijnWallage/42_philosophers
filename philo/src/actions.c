/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/07 14:17:35 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	lock_forks(philo);
	print_action(philo, FORK);
	print_action(philo, FORK);
}

void	eat(t_philo *philo)
{
	if (print_action(philo, EAT))
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->last_meal = ft_time();
		philo->nbr_meals++;
		pthread_mutex_unlock(&philo->meal_lock);
		ft_usleep(philo->table->time_to_eat);
	}
	unlock_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (print_action(philo, SLEEP))
		ft_usleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_action(philo, THINK);
}

void	die(t_philo *philo)
{
	stop(philo->table);
	pthread_mutex_lock(&philo->table->print);
	print_color(philo->index);
	print_effect(DIED);
	printf("%ld %d %s\n",
		ft_time() - philo->table->dinnertime, philo->index + 1, DIED);
	printf(RESET"");
	pthread_mutex_unlock(&philo->table->print);
}
