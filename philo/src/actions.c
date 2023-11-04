/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:04:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/03 17:25:46 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
 
bool	is_last_philo(t_philo *philo)
{
	if (philo->index == philo->nbr_philos - 1)
		return (true);
	return (false);
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

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0 && !is_last_philo(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print);
		if (*(philo->someone_died))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->print);
			return ;
		}
		print_normal(philo);
		print_normal(philo);
		pthread_mutex_unlock(philo->print);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print);
		if (*(philo->someone_died))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->print);
			return ;
		}
		print_normal(philo);
		print_normal(philo);
		pthread_mutex_unlock(philo->print);
	}
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

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		if (philo->index % 2 == 0 && !is_last_philo(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_negative(philo);
	pthread_mutex_unlock(philo->print);
	philo->last_meal = ft_time();
	philo->nbr_meals++;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_faint(philo);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_sleep);
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

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	print_italic(philo);
	pthread_mutex_unlock(philo->print);
}
