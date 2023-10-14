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
	t_arg	args;
	t_philo	*philos;

	if (!is_valid(argc, argv))
		return (handle_error(FORMAT));
	printf("Ooooh philosophizing!\n");
	args = init_args(argc, argv);
	philos = init_philos(args);
	init_mutexes();
	init_threads();
	end_threads();
	end_mutexes();
	free_all();
	return (0);
}
