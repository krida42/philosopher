/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:48:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/20 03:23:27 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_p)
{
	const t_philo	*philo = philo_p;

	printf("coucou, je suis philo: %d\n", philo->id + 1);
	while (1)
	{
		const ULONG	time = get_time()/ 1000 ;
		const ULONG	time2 = get_time() % 1000;

		printf(BLUE "Time: %lu |  %lu   philos:%d, has spoken\n" WHITE, time,time2 , philo->id);
		my_sleep(1);
	}
	return (philo_p);
}
