/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:51:08 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/07 13:43:38 by mwallage         ###   ########.fr       */
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
#define BOLD		";1m"
#define FAINT		";2m"
#define ITALIC		";3m"
#define UNDERLINE	";4m"
#define NORMAL		";6m"
#define NEGATIVE	";7m"
#define BLACK		"0"
#define RED			"1"
#define GREEN		"2"
#define YELLOW		"3"
#define BLUE		"4"
#define PINK		"5"
#define TEAL		"6"
#define WHITE		"7"
#define FORK	"has taken a fork"
#define EAT		"is eating"
#define THINK	"is thinking"
#define SLEEP	"is sleeping"
#define DIED	"died"
#define DELAY	10

# define FORMAT	"Format:\n\t./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_philo
{
	pthread_t		thread;
	int				index;
	time_t			last_meal;
	int				nbr_meals;
	pthread_mutex_t	meal_lock;
	bool			has_forks;
	t_table			*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
};

struct s_table
{
	int				nbr_philos;
	time_t			dinnertime;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	bool			someone_died;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
};

/*	dining.c	*/
void	*philosophize(void *param);
void	*monitor(void *param);
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
/*	checks.c	*/
bool	someone_died(t_table *table);
bool	someone_is_hungry(t_table *table);
bool	is_hungry(t_philo *philo);
bool	is_alive(t_philo *philo);
bool	is_last_philo(t_philo *philo);
/*	utils.c	*/
long	ft_time(void);
void	ft_usleep(int milliseconds);
void	unlock_forks(t_philo *philo);
void	lock_forks(t_philo *philo);
/*	print.c	*/
void	print_action(t_philo *philo, const char *action);
void	print_effect(const char *action);
void	print_color(int index);

#endif
