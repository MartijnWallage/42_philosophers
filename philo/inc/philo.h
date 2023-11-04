/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:51:08 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/03 17:08:08 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include "../libft/inc/libft.h"

#define RESET		"\033[0m"
#define BASE(X)		"\033[0;3"X"m"
#define BOLD(X)		"\033[3"X";1m"
#define FAINT(X)	"\033[3"X";2m"
#define	ITALIC(X)	"\033[3"X";3m"
#define UNDERLINE(X)	"\033["X";4m"
#define BLINK(X)	"\033[3"X";5m"
#define NORMAL(X)	"\033[3"X";6m"
#define NEGATIVE(X)	"\033[3"X";7m"
#define BLACK	"0"
#define RED		"1"
#define GREEN	"2"
#define YELLOW	"3"
#define BLUE	"4"
#define PINK	"5"
#define TEAL	"6"
#define WHITE	"7"

# define FORMAT	"Format:\n\t./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			last_meal;
	int				nbr_meals;
	int				max_meals;
	time_t			start_time;
	bool			*someone_died;
	pthread_mutex_t	*print;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_table
{
	int				nbr_philos;
	time_t			dinnertime;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	bool			someone_died;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
}					t_table;

/*	dining.c	*/
void	*philosophize(void *param);
void	*monitor(void *param);
bool	is_alive(t_philo *philo);
/*	actions.c	*/
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	die(t_philo *philo);
/*	end.c	*/
void	end_threads(t_table *table);
void	end_mutexes(t_table *table);
void	free_all(t_table *table);
/*	init.c	*/
int		init_args(int argc, char **argv, t_table *table);
int		init_philos(t_table *table);
int		init_forks(t_table *table);
void	init_monitor(t_table *table);
/*	utils.c	*/
long	ft_time(void);
void	ft_usleep(int milliseconds);

#endif
