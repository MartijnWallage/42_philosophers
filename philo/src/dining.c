/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/03 17:24:38 by mwallage         ###   ########.fr       */
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
	while (philo->nbr_meals < philo->max_meals)
	{
		if (i % 4 == 0)
			think(philo);
		else if (i % 4 == 1)
			take_forks(philo);
		else if (i % 4 == 2)
			eat(philo);
		else if (i % 4 == 3)
			philo_sleep(philo);
		i++;
	}
	return (NULL);
}

void	die(t_philo *philo)
{
	*(philo->someone_died) = true;
	pthread_mutex_lock(philo->print);
	printf("%ld %d has died\n", \
		ft_time() - philo->start_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
}

bool	is_alive(t_philo *philo)
{
	return (ft_time() - philo->last_meal < (long)philo->time_to_die);
}

bool	someone_is_hungry(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
		if (table->philos[i].nbr_meals < table->max_meals)
			return (true);
	return (false);
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	pthread_mutex_lock(&(table->print));
	pthread_mutex_unlock(&(table->print));
	i = 0;
	while (is_alive(&table->philos[i]))
	{
		if (!someone_is_hungry(table))
			return (NULL);
		if (i + 1 < table->nbr_philos)
			i++;
		else
			i = 0;
	}
	die(&table->philos[i]);
	return (NULL);
}
