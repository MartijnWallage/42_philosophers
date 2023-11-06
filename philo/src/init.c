/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:59 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/06 20:51:11 by mwallage         ###   ########.fr       */
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
	if (argc == 6)
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	pthread_mutex_init(&table->print, NULL);
	table->someone_died = false;
	pthread_mutex_init(&table->death_lock, NULL);
	table->dinnertime = ft_time();
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
		table->philos[i].nbr_meals = 0;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].has_forks = false;
		table->philos[i].table = table;
		if (!is_last_philo(&table->philos[i]))
			table->philos[i].left_fork = &table->forks[i + 1];
		else
			table->philos[i].left_fork = &table->forks[0];
		table->philos[i].last_meal = table->dinnertime;
		pthread_mutex_init(&table->philos[i].meal_lock, NULL);
		pthread_create(&(table->philos[i].thread), NULL, &philosophize, (void*)&table->philos[i]); 
	}	
	return (1);
}

void	init_monitor(t_table *table)
{
	pthread_create(&table->monitor, NULL, &monitor, (void *)table);
}
