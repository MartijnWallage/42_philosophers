#include "../inc/philo.h"

void	end_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->monitor, NULL);
}

void	end_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		pthread_mutex_unlock(&table->forks[i]);
		pthread_mutex_destroy(&table->forks[i]);
	}
}

void	free_all(t_table *table)
{
	free(table->philos);
	free(table->forks);
}