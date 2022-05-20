/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:48:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/20 16:57:38 by kisikaya         ###   ########.fr       */
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
		const ULONG	time = get_time()/ 1000 ;
		const ULONG	time2 = get_time() % 1000;

		printf(BLUE "Time: %lu |  %lu   philos:%d, has spoken\n" WHITE, time,time2 , philo->id + 1);
		philo->time_to_die--;
		my_sleep(100);
	}
	return (philo_p);
}

int	is_dead(t_philo *philos, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		if (philos[i].time_to_die <= 0)
		{
			printf(RED "Philosophe: %d is dead" WHITE, philos[i].id + 1);
			return (1);
		}
	}
	return (0);
}
