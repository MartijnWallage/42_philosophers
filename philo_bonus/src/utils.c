/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/15 20:14:39 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	ft_usleep(int milliseconds)
{
	long	time;

	time = ft_time();
	while (ft_time() < time + milliseconds)
		usleep(milliseconds / 100);
}

int	mealtime(int round, t_table *table)
{
	if (round == 0)
		return (0);
	if (round == 1)
		return (table->time_to_eat);
	return (ft_max(
		mealtime(round - 1, table) + table->time_to_eat,
		mealtime(round - 2, table) + table->time_to_sleep));
}

int	which_round(t_philo *philo)
{
	int	new_index;

	if (philo->table->nbr_philos / 2 == 0)
		return (0);
	new_index = philo->index + philo->table->nbr_philos * philo->nbr_meals;
	return (new_index / (philo->table->nbr_philos / 2));
}