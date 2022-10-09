#include "philo.h"

void	*monitor_routine(void *table_p)
{
	int		i;
	t_table	*table;
	
	table = table_p;
	
	printf("MONOTOR\n");
	while (table->nb_loaded < table->nb_philo)
		;
	table->start_time = get_time();
	usleep(500);
	while (1)
	{
		pthread_mutex_lock(&table->mut_is_dead);
		i = -1;
		while (table->philos[++i].id != -1)
			if (get_time() >= table->philos[i].time_to_die)
			{
				table->is_dead = 1;
				pthread_mutex_unlock(&table->mut_is_dead);
				return (NULL);
			}
		pthread_mutex_unlock(&table->mut_is_dead);
		usleep(1000);
	}
}

int	start_monitor(t_table *table)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, table))
		return (printf("failed to create monitor thread !\n"), 1);
	return (0);
}
