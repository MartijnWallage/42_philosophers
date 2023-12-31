/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/11 16:09:09 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_valid(int argc)
{
	if (argc != 5 && argc != 6)
		return (handle_error(FORMAT));
	return (1);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!is_valid(argc))
		return (1);
	if (!init_args(argc, argv, &table))
		return (1);
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
