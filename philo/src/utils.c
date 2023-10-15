/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:21 by mwallage          #+#    #+#             */
/*   Updated: 2023/10/14 16:59:01 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_time(void)
{
	struct timeval	timeval;
	long			res;

	gettimeofday(&timeval, NULL);
	res = 1000 * (size_t)timeval.tv_sec + (size_t)timeval.tv_usec / 1000;
	return (res);
}