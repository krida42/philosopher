/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:53:16 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/25 00:49:12 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		forks_available(t_philo *philo)
{
	const t_table	*table = philo->table;
	if (table->forks[philo->fork_l] && table->forks[philo->fork_r])
		return (1);
	return (0);
}

int		eating(t_philo *philo)
{
	if (get_time() >= philo->time_to_eat)
		return (0);
	return (1);
}


int		sleeping(t_philo *philo)
{
	if (get_time() >= philo->time_to_sleep)
		return (0);
	return (1);
}

void	describe_end(t_philo *philos)
{
	int				i;
	int				counter;
	const t_table	*table = philos[0].table;

	counter = 0;
	i = -1;
	while (philos[++i].id != -1 && philos[i].remains_eat == 0)
		counter++;
	if (counter == table->nb_philo)
	{
		printf(GREEN "All Philosophers have eaten %ld times\n" WHITE,
				table->nb_must_eat);
		return ;
	}
	i = -1;
	while (philos[++i].id != -1)
	{
		if (get_time () >= philos[i].time_to_die)
			printf(RED "Philosopher id: %d is dead\n" WHITE, philos[i].id + 1);
	}
}
