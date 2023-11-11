/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/11 16:52:07 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_action(philo, FORK);
	sem_wait(philo->table->forks);
	print_action(philo, FORK);
}

void	eat(t_philo *philo)
{
	philo->last_meal = ft_time();
	philo->nbr_meals++;
	ft_usleep(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_action(philo, THINK);
}
