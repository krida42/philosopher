/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:53:16 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/22 00:19:22 by kisikaya         ###   ########.fr       */
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
	if (philo->time_to_eat <= 0)
	{
		philo->time_to_eat = philo->table->time_to_eat;
		return (0);
	}
	philo->time_to_eat--;
	philo->time_to_die += 2;
	return (1);
}


int		sleeping(t_philo *philo)
{
	if (philo->time_to_sleep <= 0)
	{
		philo->time_to_sleep = philo->table->time_to_sleep;
		return (0);
	}
	philo->time_to_sleep--;
	return (1);
}

void	describe_end(t_philo *philos)
{
	int	i;

	i = -1;
	while (philos[++i].id != -1)
	{
		if (philos[i].time_to_die <= 0)
			printf(RED "Philosopher id: %d is dead\n" WHITE, philos[i].id + 1);
	}
}
