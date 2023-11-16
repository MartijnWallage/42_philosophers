/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:19:18 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 13:02:03 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_color(int index)
{
	printf("\033[3");
	if (index % 7 == 0)
		printf(RED"");
	else if (index % 7 == 1)
		printf(GREEN"");
	else if (index % 7 == 2)
		printf(YELLOW"");
	else if (index % 7 == 3)
		printf(BLUE"");
	else if (index % 7 == 4)
		printf(PINK"");
	else if (index % 7 == 5)
		printf(TEAL"");
	else if (index % 7 == 6)
		printf(WHITE"");
}

void	print_effect(const char *action)
{
	if (ft_strcmp(action, FORK) == 0)
		printf(NORMAL"");
	else if (ft_strcmp(action, THINK) == 0)
		printf(ITALIC"");
	else if (ft_strcmp(action, SLEEP) == 0)
		printf(FAINT"");
	else if (ft_strcmp(action, EAT) == 0)
		printf(UNDERLINE"");
	else if (ft_strcmp(action, DIED) == 0)
		printf(NEGATIVE"");
	else
		printf(NORMAL"");
}

void	print_action(t_philo *philo, const char *action)
{
	sem_wait(philo->table->print);
	print_color(philo->index);
	print_effect(action);
	printf("%ld %d %s\n",
		ft_time() - philo->table->dinnertime, philo->index + 1, action);
	write(STDOUT_FILENO, RESET, 5);
	if (*action != 'd' && !(is_last_philo(philo) && !is_hungry(philo)))
		sem_post(philo->table->print);
}
