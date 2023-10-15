/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/10/14 16:59:01 by mwallage         ###   ########.fr       */
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

void	init_args(int argc, char **argv, t_table *table)
{
	table->start_time = 
	table->nbr_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nbr_meals = ft_atoi(argv[5]);
	else
		table->nbr_meals = -1;
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!is_valid(argc, argv))
		return (handle_error(FORMAT));
	printf("Ooooh philosophizing!\n");
	init_args(argc, argv, &table);
	init_philos(&table);
	init_mutexes(&table);
	init_threads(&table);
	end_threads(&table);
	end_mutexes(&table);
	free_all(&table);
	return (0);
}
