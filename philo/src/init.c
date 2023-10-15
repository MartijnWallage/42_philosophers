#include "../inc/philo.h"

void	init_args(int argc, char **argv, t_table *table)
{
	table->nbr_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->start_time = ft_time();
	if (argc == 6)
		table->nbr_meals = ft_atoi(argv[5]);
	else
		table->nbr_meals = -1;
}

void	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	// protect malloc
	i = -1;
	while (++i < table->nbr_philos)
		pthread_mutex_init(&(table->forks[i]), NULL);
}

void	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	// protect malloc
	i = -1;
	while (++i < table->nbr_philos)
	{
		table->philos[i].index = i;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].alive = true;
		pthread_mutex_init(&table->philos[i].lock_print, NULL);
		table->philos[i].left_fork = NULL;
		table->philos[i].right_fork = NULL;
		pthread_create(&(table->philos[i].thread), NULL, &philosophize, (void*)&table->philos[i]); 
	}	
}

void	init_monitor(t_table *table)
{
	pthread_create(&table->monitor, NULL, &monitor, (void *)table);
}