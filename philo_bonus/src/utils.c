/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 14:54:42 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_time(void)
{
	struct timeval	tv;
	unsigned int	res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

unsigned int	current_time(t_philo *philo)
{
	return ((int)(ft_time() - philo->table->dinnertime));
}

void	ft_usleep(unsigned int milliseconds)
{
	unsigned int	time;

	time = ft_time();
	while (ft_time() < time + milliseconds)
		usleep(milliseconds / 100);
}

unsigned int	mealtime(unsigned int round, t_table *table)
{
	unsigned int	wait;
	unsigned int	ret;

	if (table->time_to_sleep <= table->time_to_eat)
		return (round * table->time_to_eat);
	wait = table->time_to_eat + table->time_to_sleep;
	ret = 0;
	if (round % 2 == 1)
	{
		round--;
		ret += table->time_to_eat;
	}
	ret += (round / 2 * wait);
	return (ret);
}

unsigned int	which_round(t_philo *philo)
{
	unsigned int	new_index;

	if (philo->table->nbr_philos / 2 == 0)
		return (0);
	new_index = philo->index + philo->table->nbr_philos * philo->nbr_meals;
	return (new_index / (philo->table->nbr_philos / 2));
}
