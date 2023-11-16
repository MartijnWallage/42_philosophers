/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:51:08 by mwallage          #+#    #+#             */
/*   Updated: 2023/11/16 15:15:40 by mwallage         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/inc/libft.h"

# define RESET		"\033[0m"
# define BOLD		";1m"
# define FAINT		";2m"
# define ITALIC		";3m"
# define UNDERLINE	";4m"
# define NORMAL		";6m"
# define NEGATIVE	";7m"
# define BLACK		"0"
# define RED		"1"
# define GREEN		"2"
# define YELLOW		"3"
# define BLUE		"4"
# define PINK		"5"
# define TEAL		"6"
# define WHITE		"7"
# define FORK		"has taken a fork"
# define EAT		"is eating"
# define THINK		"is thinking"
# define SLEEP		"is sleeping"
# define DIED		"died"

# define FORMAT	"Format:\n\t./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_philo
{
	pid_t			pid;
	int				index;
	pthread_t		monitor;
	time_t			last_meal;
	int				nbr_meals;
	pthread_mutex_t	meal_lock;
	t_table			*table;
};

struct s_table
{
	int				nbr_philos;
	time_t			dinnertime;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	sem_t			*death;
	sem_t			*stop;
	sem_t			*print;
	sem_t			*forks;
	t_philo			*philos;
};

/*	dining.c	*/
void	*monitor(void *param);
void	dream(t_philo *philo);
void	*philosophize(void *param);
/*	actions.c	*/
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	philo_sleep(t_philo *philo);
bool	is_last_meal(t_philo *philo);
/*	end.c	*/
void	end_all(t_table *table);
void	close_some(sem_t *a, sem_t *b, sem_t *c, sem_t *d);
/*	init.c	*/
int		init_args(int argc, char **argv, t_table *table);
int		init_philos(t_table *table);
int		init_table(t_table *table);
/*	checks.c	*/
bool	is_hungry(t_philo *philo);
bool	is_alive(t_philo *philo);
bool	is_last_philo(t_philo *philo);
bool	is_someone_hungry(t_philo *philo);
/*	utils.c	*/
unsigned int	ft_time(void);
unsigned int	current_time(t_philo *philo);
void			ft_usleep(unsigned int milliseconds);
unsigned int	mealtime(unsigned int round, t_table *table);
unsigned int	which_round(t_philo *philo);
/*	print.c	*/
void	print_action(t_philo *philo, const char *action);
void	print_effect(const char *action);
void	print_color(int index);
int		handle_error(char *message);

#endif
