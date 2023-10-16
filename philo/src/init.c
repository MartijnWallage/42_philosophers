/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:59 by mwallage          #+#    #+#             */
/*   Updated: 2023/10/16 14:05:01 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_args(int argc, char **argv, t_table *table)
{
	table->nbr_philos = ft_atoi(argv[1]);
	if (table->nbr_philos < 0)
		return (0);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->dinnertime = ft_time();
	if (argc == 6)
		table->nbr_meals = ft_atoi(argv[5]);
	else
		table->nbr_meals = -1;
	pthread_mutex_init(&(table->print), NULL);
	return (1);
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (table->forks == NULL)
		return (0);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_mutex_init(&(table->forks[i]), NULL);
	return (1);
}

int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (table->philos == NULL)
		return (0);
	i = -1;
	while (++i < table->nbr_philos)
	{
		table->philos[i].index = i;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].alive = true;
		table->philos[i].stop = false;
		table->philos[i].start_time = ft_time();
		table->philos[i].last_meal = table->philos[i].start_time;
		table->philos[i].nbr_meals = 0;
		table->philos[i].print = &(table->print);
		table->philos[i].left_fork = &table->forks[i];
		if (i + 1 < table->nbr_philos)
			table->philos[i].right_fork = &table->forks[i + 1];
		else
			table->philos[i].right_fork = &table->forks[0];
		pthread_mutex_init(&(table->philos[i].alive_lock), NULL);
		pthread_mutex_init(&(table->philos[i].stop_lock), NULL);
		pthread_create(&(table->philos[i].thread), NULL, &philosophize, (void*)&table->philos[i]); 
	}	
	return (1);
}

void	init_monitor(t_table *table)
{
	pthread_create(&table->monitor, NULL, &monitor, (void *)table);
}
