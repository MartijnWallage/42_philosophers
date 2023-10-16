/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/10/15 20:12:14 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	handle_error(char *message)
{
	printf("%s\n", message);
	return (1);
}

int	is_valid(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (0);
	if (ft_atoi(argv[1]) == 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!is_valid(argc, argv))
		return (handle_error(FORMAT));
	printf("Ooooh philosophizing!\n");
	if (!init_args(argc, argv, &table))
		return (1);
	pthread_mutex_lock(&(table.print));
	printf("Dinner started at %ld.\n", table.dinnertime);
	printf("There are %d philosophers.\n", table.nbr_philos);
	printf("Each can survive for %d milliseconds without eating.\n", table.time_to_die);
	printf("Each takes %d milliseconds to eat.\n", table.time_to_eat);
	printf("Each sleeps for %d milliseconds.\n", table.time_to_sleep);
	pthread_mutex_unlock(&(table.print));
	if (!init_forks(&table))
		return (1);
	if (!init_philos(&table))
		return (1);
	init_monitor(&table);
	end_threads(&table);
	end_mutexes(&table);
	free_all(&table);
	return (0);
}
