/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:59 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 15:17:53 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(int argc, char **argv, t_table *table)
{
	table->nbr_philos = ft_atoi(argv[1]);
	if (table->nbr_philos <= 0)
		return (handle_error("invite at least one philosopher to dinner"));
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat < 60)
		return (handle_error("time to eat must be at least 60 ms"));
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die < 60)
		return (handle_error("time to die must be at least 60 ms"));
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep < 60)
		return (handle_error("time to sleep must be at least 60 ms"));
	if (argc == 6)
		table->max_meals = ft_max(0, ft_atoi(argv[5]));
	else
		table->max_meals = -1;
	return (1);
}

int	init_table(t_table *table)
{
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("forks");
	table->death = sem_open("death", O_CREAT, 0600, 1);
	table->print = sem_open("print", O_CREAT, 0600, 1);
	table->stop = sem_open("stop", O_CREAT, 0600, 1);
	table->forks = sem_open("forks", O_CREAT, 0600, table->nbr_philos);
	if (table->death == SEM_FAILED || table->print == SEM_FAILED
		|| table->stop == SEM_FAILED || table->forks == SEM_FAILED)
	{
		close_some(table->death, table->print, table->stop, table->forks);
		return (handle_error("semaphore failed"));
	}
	table->dinnertime = ft_time();
	return (1);
}

int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (table->philos == NULL)
		return (end_all(table), handle_error("malloc failed"));
	i = -1;
	while (++i < table->nbr_philos)
	{
		table->philos[i].index = i;
		table->philos[i].nbr_meals = 0;
		table->philos[i].table = table;
		table->philos[i].last_meal = table->dinnertime;
		pthread_mutex_init(&table->philos[i].meal_lock, NULL);
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (end_all(table), free(table->philos),
				handle_error("fork failed"));
		if (table->philos[i].pid == 0)
		{
			philosophize((void *)&table->philos[i]);
			exit(0);
		}
	}
	return (1);
}
