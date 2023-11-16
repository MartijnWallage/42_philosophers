/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 14:08:15 by mwallage         ###   ########.fr       */
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

int	current_time(t_philo *philo)
{
	return ((int)(ft_time() - philo->table->dinnertime));
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
	int	wait;
	int	ret;
	
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
	
/* 	if (table->time_to_sleep > 2 * tble->time_to_eat)
	{
		if (round % 2 == 0)
			return (round / 2 * table->time_to_sleep);
		round--;
		return (table->time_to_eat + (round / 2) * table->time_to_sleep);
	}
	if (table->time_to_sleep > table->time_to_eat)
	{
		if (round % 2 == 0)
			return ((round / 2) * (table->time_to_eat + table->time_to_sleep));
		round--;
		return (table->time_to_eat + (round / 2) * (table->time_to_eat + table->time_to_sleep));
	}
	return (round * table->time_to_eat); */
}

/*	What if tte < tts < 2 * tte?
	
	0			tte + tts		4tte + 2 * tts
	0			2tte + tts		4tte + 2 * tts
	tte			2tte + tts		4tte + 3 * tts
	tte			3tte + 2 * tts	4tte + 3 * tts
	tte + tts	3tte + 2 * tts
	
*/
  
int	which_round(t_philo *philo)
{
	int	new_index;

	if (philo->table->nbr_philos / 2 == 0)
		return (0);
	new_index = philo->index + philo->table->nbr_philos * philo->nbr_meals;
	return (new_index / (philo->table->nbr_philos / 2));
}