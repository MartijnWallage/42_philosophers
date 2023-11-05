/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:19:18 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/05 11:21:06 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_underline(t_philo *philo)
{
	if (philo->index % 6 == 0)
		printf(UNDERLINE(RED)"%ld %d has died\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 1)
		printf(UNDERLINE(YELLOW)"%ld %d has died\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 2)
		printf(UNDERLINE(BLUE)"%ld %d has died\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 3)
		printf(UNDERLINE(PINK)"%ld %d has died\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 4)
		printf(UNDERLINE(TEAL)"%ld %d has died\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 5)
		printf(UNDERLINE(WHITE)"%ld %d has died\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
}

void	print_normal(t_philo *philo)
{
	if (philo->index % 6 == 0)
		printf(NORMAL(RED)"%ld %d has taken a fork\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 1)
		printf(NORMAL(YELLOW)"%ld %d has taken a fork\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 2)
		printf(NORMAL(BLUE)"%ld %d has taken a fork\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 3)
		printf(NORMAL(PINK)"%ld %d has taken a fork\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 4)
		printf(NORMAL(TEAL)"%ld %d has taken a fork\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 5)
		printf(NORMAL(WHITE)"%ld %d has taken a fork\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
}

void	print_negative(t_philo *philo)
{
	if (philo->index % 6 == 0)
		printf(NEGATIVE(RED)"%ld %d is eating\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 1)
		printf(NEGATIVE(YELLOW)"%ld %d is eating\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 2)
		printf(NEGATIVE(BLUE)"%ld %d is eating\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 3)
		printf(NEGATIVE(PINK)"%ld %d is eating\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 4)
		printf(NEGATIVE(TEAL)"%ld %d is eating\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 5)
		printf(NEGATIVE(WHITE)"%ld %d is eating\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
}

void	print_faint(t_philo *philo)
{
	if (philo->index % 6 == 0)
		printf(FAINT(RED)"%ld %d is sleeping\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 1)
		printf(FAINT(YELLOW)"%ld %d is sleeping\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 2)
		printf(FAINT(BLUE)"%ld %d is sleeping\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 3)
		printf(FAINT(PINK)"%ld %d is sleeping\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 4)
		printf(FAINT(TEAL)"%ld %d is sleeping\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 5)
		printf(FAINT(WHITE)"%ld %d is sleeping\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
}

void	print_italic(t_philo *philo)
{
	if (philo->index % 6 == 0)
		printf(ITALIC(RED)"%ld %d is thinking\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 1)
		printf(ITALIC(YELLOW)"%ld %d is thinking\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 2)
		printf(ITALIC(BLUE)"%ld %d is thinking\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 3)
		printf(ITALIC(PINK)"%ld %d is thinking\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 4)
		printf(ITALIC(TEAL)"%ld %d is thinking\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
	else if (philo->index % 6 == 5)
		printf(ITALIC(WHITE)"%ld %d is thinking\n"RESET, \
			ft_time() - philo->start_time, philo->index + 1);
}