/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 15:09:05 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!init_table(&table))
		return (1);
	sem_wait(table.stop);
	if (!init_philos(&table))
		return (1);
	sem_wait(table.stop);
	end_all(&table);
	free(table.philos);
	return (0);
}
