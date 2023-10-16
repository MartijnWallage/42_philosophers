/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/10/16 14:04:46 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosophize(void *param)
{
	t_philo	*philo;
	char	i;

	philo = (t_philo *)param;
	philo->start_time = ft_time();
	philo->last_meal = philo->start_time;
	i = 0;
	while (!*(philo->stop))
	{
		if (i % 4 == 0 && !*(philo->stop))
			think(philo);
		else if (i % 4 == 1 && !*(philo->stop))
			take_forks(philo);
		else if (i % 4 == 2 && !*(philo->stop))
			eat(philo);
		else if (i % 4 == 3 && !*(philo->stop))
			philo_sleep(philo);
		i++;
	}
	return (NULL);
}

void	*die(t_philo	*philo)
{
	pthread_mutex_lock(philo->print);
	printf("%ld %d has died\n", \
		ft_time() - philo->start_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
	*(philo->stop) = true;
	return (NULL);
}

bool	is_alive(t_philo *philo)
{
	return (ft_time() - philo->last_meal < (long)philo->time_to_die);
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	pthread_mutex_lock(&(table->print));
	pthread_mutex_unlock(&(table->print));
	i = 0;
	while (is_alive(&(table->philos[i])))
	{
		if (i + 1 < table->nbr_philos)
			i++;
		else
			i = 0;
	}
	return (die(&(table->philos[i])));
}
