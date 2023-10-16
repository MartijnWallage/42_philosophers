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
	printf("Philosopher %d has sat down at the table on %ld.\n", philo->index + 1, philo->start_time);
	i = 0;
	while (!philo->stop && philo->alive)
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

void	die(t_philo	*philo)
{
	pthread_mutex_lock(philo->print);
	printf("%ld %d has died\n", \
		ft_time() - philo->start_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
	philo->alive = false;
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	pthread_mutex_lock(&(table->print));
	printf("I'm watching the philosophers having a symposium\n");
	printf("There are %d of them\n", table->nbr_philos);
	printf("%d too many, if you ask me!\n", table->nbr_philos);
	pthread_mutex_unlock(&(table->print));
	i = 0;
	while (1)
	{
		if (ft_time() - table->philos[i].last_meal > table->philos[i].time_to_die)
		{
			die(&(table->philos[i]));
			i = -1;
			while (++i < table->nbr_philos)
				table->philos[i].stop = true;
			return (NULL);
		}
		if (i + 1 < table->nbr_philos)
			i++;
		else
			i = 0;
	}
	return (NULL);
}
