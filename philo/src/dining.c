#include "../inc/philo.h"

void	*philosophize(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	printf("This is philosopher %d.\n", philo->index);
	printf("I'm currently thinking\nI don't need to eat.\n");
	return (NULL);
}

void	*monitor(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	printf("I'm watching the philosophers thinking\n");
	printf("There are %d of them", table->nbr_philos);
	return (NULL);
}
