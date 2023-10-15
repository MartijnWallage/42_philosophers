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

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!is_valid(argc, argv))
		return (handle_error(FORMAT));
	printf("Ooooh philosophizing!\n");
	init_args(argc, argv, &table);
	init_forks(&table);
	init_philos(&table);
	init_monitor(&table);
	end_threads(&table);
	end_mutexes(&table);
	free_all(&table);
	return (0);
}
