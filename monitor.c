/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:55:31 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/13 19:19:04 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*monitor_routine(void *table_p)
{
	int		i;
	t_table	*table;

	table = table_p;
	while (get_time() < (table->start_time + 8))
		usleep(2000);
	while (1)
	{
		i = -1;
		while (table->philos[++i].id != -1)
		{
			pthread_mutex_lock(&table->philos[i].mut_time_to_die);
			if (table->philos[i].time_to_die > 0
				&& get_time() >= table->philos[i].time_to_die)
			{
				pthread_mutex_unlock(&table->philos[i].mut_time_to_die);
				pthread_mutex_lock(&table->mut_is_dead);
				table->is_dead = table->philos[i].id + 1;
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
	if (pthread_join(monitor, NULL))
		return (printf("failed to join monitor thread !\n"), 1);
	return (0);
}
