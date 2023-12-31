/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:59 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/17 17:19:08 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_args(int argc, char **argv, t_table *table)
{
	table->nbr_philos = ft_atoi(argv[1]);
	if (table->nbr_philos <= 0)
		return (handle_error("invite at least one philosopher"));
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die < 60)
		return (handle_error("time to die must be at least 60 ms"));
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat < 60)
		return (handle_error("time to eat must be at least 60 ms"));
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep < 60)
		return (handle_error("time to sleep must be at least 60 ms"));
	if (argc == 6)
		table->max_meals = ft_max(0, ft_atoi(argv[5]));
	else
		table->max_meals = -1;
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->stop_lock, NULL);
	table->stop = false;
	table->dinnertime = ft_time();
	return (1);
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (table->forks == NULL)
		return (handle_error("malloc failed"));
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
		return (free(table->forks), handle_error("malloc failed"));
	i = -1;
	while (++i < table->nbr_philos)
	{
		table->philos[i].index = i;
		table->philos[i].nbr_meals = 0;
		table->philos[i].table = table;
		table->philos[i].last_meal = table->dinnertime;
		table->philos[i].has_forks = false;
		table->philos[i].right_fork = &table->forks[i];
		if (!is_last_philo(&table->philos[i]))
			table->philos[i].left_fork = &table->forks[i + 1];
		else
			table->philos[i].left_fork = &table->forks[0];
		pthread_mutex_init(&table->philos[i].meal_lock, NULL);
		pthread_create(&(table->philos[i].thread),
			NULL, &philosophize, (void*)&table->philos[i]);
	}
	return (1);
}

void	init_monitor(t_table *table)
{
	pthread_create(&table->monitor, NULL, &monitor, (void *)table);
}
