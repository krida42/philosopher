/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:53:16 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/13 19:26:22 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	forks_available(t_philo *philo)
{
	const t_table	*table = philo->table;

	if (table->forks[philo->fork_l] && table->forks[philo->fork_r])
		return (1);
	return (0);
}
*/
int	eating(t_philo *philo)
{
	if (get_time() >= philo->time_to_eat)
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (get_time() >= philo->time_to_sleep)
		return (0);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (get_time() >= philo->time_to_think)
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
		pthread_mutex_lock(&philos[0].table->mut_display);
		printf(GREEN "All Philosophers have eaten %ld times\n" WHITE,
			table->nb_must_eat);
		pthread_mutex_unlock(&philos[0].table->mut_display);
		return ;
	}
	if (table->is_dead)
		print_status(RED"%lu %d has died"WHITE, &philos[table->is_dead - 1]);
}
