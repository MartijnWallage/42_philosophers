/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:19:18 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 13:02:30 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_color(int index)
{
	printf("\033[3");
	if (index % 6 == 0)
		printf(RED"");
	else if (index % 6 == 1)
		printf(GREEN"");
	else if (index % 6 == 2)
		printf(YELLOW"");
	else if (index % 6 == 3)
		printf(BLUE"");
	else if (index % 6 == 4)
		printf(PINK"");
	else if (index % 6 == 5)
		printf(TEAL"");
}

void	print_effect(const char *action)
{
	if (ft_strcmp(action, FORK) == 0)
		printf(BOLD"");
	else if (ft_strcmp(action, THINK) == 0)
		printf(ITALIC"");
	else if (ft_strcmp(action, SLEEP) == 0)
		printf(FAINT"");
	else if (ft_strcmp(action, EAT) == 0)
		printf(UNDERLINE"");
	else if (ft_strcmp(action, DIED) == 0)
		printf(NEGATIVE"");
}

int	print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->table->print);
	if (is_stop(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print);
		return (0);
	}
	print_color(philo->index);
	print_effect(action);
	printf("%ld %d %s\n",
		ft_time() - philo->table->dinnertime, philo->index + 1, action);
	write(STDOUT_FILENO, RESET, 5);
	pthread_mutex_unlock(&philo->table->print);
	return (1);
}

int	handle_error(char *message)
{
	printf("philosophers: ");
	printf("%s\n", message);
	return (0);
}
