/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 22:29:52 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_action(philo, FORK);
	sem_wait(philo->table->forks);
	print_action(philo, FORK);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->table->death);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = ft_time();
	philo->nbr_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	if (is_someone_hungry(philo))
		print_action(philo, EAT);
	sem_post(philo->table->death);
	ft_usleep(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep);
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

void	think(t_philo *philo)
{
	print_action(philo, THINK);
	dream(philo);
}
