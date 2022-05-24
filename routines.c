/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:48:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/25 00:03:59 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	move_fork(t_philo *philo, int take)
{
	const t_table	*table = philo->table;
	const ULONG		timestamp = get_time() - philo->table->start_time;

	pthread_mutex_lock(&philo->table->mut_display);
	if (take)
	{
		if (!table->forks[philo->fork_l] || !table->forks[philo->fork_r])
			exit (printf(RED "trying to get forks somehere theres isnt fork, id: %d\n" WHITE, philo->id));
	}
	else 
	{
		if (table->forks[philo->fork_l] || table->forks[philo->fork_r])
			exit (printf(RED "trying to putback forks somehere theres is already fork" WHITE));
	}
	table->forks[philo->fork_l] = !take;
	table->forks[philo->fork_r] = !take;
	if (take)
	{
		printf("%lu %d has taken a fork\n", timestamp, philo->id + 1);
		printf("%lu %d has taken a fork\n", timestamp, philo->id + 1);

	}
	pthread_mutex_unlock(&philo->table->mut_display);
}

static void	set_state(t_philo *philo, int state)
{
	const ULONG	timestamp = get_time() - philo->table->start_time;

	pthread_mutex_lock(&philo->table->mut_display);
	if (state == 0)
		printf("%lu %d is thinking\n", timestamp, philo->id + 1);
	else if (state == 1)
	{
		//philo->time_to_die = philo->time_to_die + philo->table->time_to_eat * 2;
		philo->time_to_eat = get_time() + philo->table->time_to_eat;
		printf("%lu %d is eating\n", timestamp, philo->id + 1);
	}
	else if (state == 2)
	{
		philo->time_to_sleep = get_time() + philo->table->time_to_sleep;
		printf("%lu %d is sleeping\n", timestamp, philo->id + 1);
	}
	philo->state = state;
	pthread_mutex_unlock(&philo->table->mut_display);
}

static void	do_action(t_philo *philo)
{
	int	is_odd;

	is_odd = philo->id % 2;
	if (philo->state == -1)
	{
		if (is_odd)
			move_fork(philo, 1);
		set_state(philo, is_odd);
	}
	else if (philo->state == 0)
	{
		if (forks_available(philo))
		{
			move_fork(philo, 1);
			set_state(philo, 1);
		}
	}
	else if (philo->state == 1)
	{
		if (!eating(philo))
		{
			philo->time_to_die += philo->table->time_to_die;
			move_fork(philo, 0);
			set_state(philo, 2);
		}
	}
	else if (philo->state == 2)
	{
		if (!sleeping(philo))
			set_state(philo, 0);
	}
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = philo_p;
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		if (get_time() >= philo->time_to_die)
			philo->table->is_dead = 1;
		if (philo->table->is_dead)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return (NULL);
		}
		do_action(philo);
		pthread_mutex_unlock(&philo->table->mutex);
		usleep(250);
	}
	return (NULL);
}

