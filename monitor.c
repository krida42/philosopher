#include "philo.h"
#include <pthread.h>

void	*monitor_routine(void *table_p)
{
	int		i;
	t_table	*table;

	table = table_p;

	printf("MONOTOR\n");
	while (get_time() < table->start_time)
		;
	while (1)
	{
		i = -1;
		while (table->philos[++i].id != -1)
		{
			pthread_mutex_lock(&table->philos[i].mut_time_to_die);
			if (get_time() >= table->philos[i].time_to_die)
			{
				pthread_mutex_unlock(&table->philos[i].mut_time_to_die);
				pthread_mutex_lock(&table->mut_is_dead);
				table->is_dead = 1;
				pthread_mutex_unlock(&table->mut_is_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos[i].mut_time_to_die);
		}
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
