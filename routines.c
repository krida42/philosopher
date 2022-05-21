/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:48:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/21 18:38:44 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = philo_p;

	printf("coucou, je suis philo: %d\n", philo->id + 1);
	while (1)
	{
		const ULONG	time = get_time() / 1000 ;
		const ULONG	time2 = get_time() % 1000;

		printf(BLUE "Time: %lu |  %lu   philos:%d, has spoken\n" WHITE, time,time2 , philo->id + 1);
		pthread_mutex_lock(&philo->table->mutex);
		if (philo->time_to_die <= 0)
			philo->table->is_dead = 1;
		if (philo->table->is_dead)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->mutex);
		pthread_mutex_lock(&philo->mutex);
		philo->time_to_die--;
		pthread_mutex_unlock(&philo->mutex);
		my_sleep(1);
	}
	return (NULL);
}
