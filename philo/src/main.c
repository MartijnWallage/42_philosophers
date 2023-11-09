/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 19:12:55 by mwallage         ###   ########.fr       */
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
	if (!init_args(argc, argv, &table))
		return (handle_error("number of philosophers must be more than 0"));
	if (!init_forks(&table))
		return (handle_error("malloc failed"));
	if (!init_philos(&table))
		return (handle_error("malloc failed"));
	init_monitor(&table);
	end_threads(&table);
	end_mutexes(&table);
	free_all(&table);
	return (0);
}
