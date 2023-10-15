#include "../inc/philo.h"

void	*philosophize(void *param)
{
	t_philo	*philo;
	char	i;

	philo = (t_philo *)param;
	philo->birthtime = ft_time();
	philo->last_meal = philo->birthtime;
	printf("Philosopher %d was born on %ld.\n", philo->index, philo->birthtime);
	i = 0;
	while (philo->alive)
	{
		if (i % 4 == 0)
			take_forks(philo);
		else if (i % 4 == 1)
			eat(philo);
		else if (i % 4 == 2)
			sleep(philo);
		else if (i % 4 == 3)
			think(philo);
		i++;
	}
	return (NULL);
}

void	*monitor(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	printf("I'm watching the philosophers thinking\n");
	printf("There are %d of them\n", table->nbr_philos);
	return (NULL);
}
