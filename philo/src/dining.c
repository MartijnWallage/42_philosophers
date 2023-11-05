/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 11:57:39 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	has_eaten_enough(t_philo *philo)
{
	if (philo->max_meals == -1)
		return (false);
	return (philo->nbr_meals >= philo->max_meals);
}

void	*philosophize(void *param)
{
	t_philo	*philo;
	char	i;

	philo = (t_philo *)param;
	philo->start_time = ft_time();
	philo->last_meal = philo->start_time;
	i = 0;
	while (!*philo->someone_died && !has_eaten_enough(philo))
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
	print_underline(philo);
	pthread_mutex_unlock(philo->print);
}

bool	is_alive(t_philo *philo)
{
	return (ft_time() - philo->last_meal < (long)philo->time_to_die);
}

bool	someone_is_hungry(t_table *table)
{
	int	i;

	if (table->max_meals == -1)
		return (true);
	i = -1;
	while (++i < table->nbr_philos)
		if (!has_eaten_enough(&table->philos[i]))
			return (true);
	return (false);
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	i = 0;
	while (is_alive(&table->philos[i]))
	{
		if (!someone_is_hungry(table))
			return (NULL);
		if (++i == table->nbr_philos)
			i = 0;
	}
	die(&table->philos[i]);
	return (NULL);
}
