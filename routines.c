/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:48:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/13 18:55:11 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

static void	move_fork(t_philo *philo, int take)
{
	const t_table	*table = philo->table;

	if (!take)
	{
		pthread_mutex_unlock(table->forks + philo->fork_r);
		pthread_mutex_unlock(table->forks + philo->fork_l);
		return ;
	}
	if (philo->id % 2)
	{
		pthread_mutex_lock(table->forks + philo->fork_r);
		print_status("%lu %d has taken a fork\n", philo);
		pthread_mutex_lock(table->forks + philo->fork_l);
		print_status("%lu %d has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(table->forks + philo->fork_l);
		print_status("%lu %d has taken a fork\n", philo);
		pthread_mutex_lock(table->forks + philo->fork_r);
		print_status("%lu %d has taken a fork\n", philo);
	}
}

static void	set_state(t_philo *philo, int state)
{
	if (state == THINK)
	{
		philo->time_to_think = 0;
		if (philo->table->nb_philo % 2
			&& philo->table->time_to_eat >= philo->table->time_to_sleep)
			philo->time_to_think = get_time() + philo->table->time_to_think;
		print_status("%lu %d is thinking\n", philo);
	}
	else if (state == EAT)
	{
		philo->time_to_eat = get_time() + philo->table->time_to_eat;
		pthread_mutex_lock(&philo->mut_time_to_die);
		philo->time_to_die = get_time() + philo->table->time_to_die;
		pthread_mutex_unlock(&philo->mut_time_to_die);
		print_status("%lu %d is eating\n", philo);
	}
	else if (state == SLEEP)
	{
		philo->time_to_sleep = get_time() + philo->table->time_to_sleep;
		print_status("%lu %d is sleeping\n", philo);
	}
	philo->state = state;
}

static void	first_action(t_philo *philo)
{
	const int	is_odd = philo->id % 2;

	if (is_odd)
		move_fork(philo, 1);
	set_state(philo, is_odd);
	if (!is_odd)
		usleep(5000);
}

static void	do_action(t_philo *philo)
{
	if (philo->state == -1)
		first_action(philo);
	else if (philo->state == THINK && philo->table->nb_philo > 1)
	{
		if (!thinking(philo))
		{
			move_fork(philo, 1);
			set_state(philo, EAT);
		}
	}
	else if (philo->state == EAT)
	{
		if (!eating(philo))
		{
			move_fork(philo, 0);
			if (--philo->remains_eat == 0)
				return ;
			set_state(philo, SLEEP);
		}
	}
	else if (philo->state == SLEEP)
		if (!sleeping(philo))
			set_state(philo, THINK);
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = philo_p;
	wait_routine(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mut_is_dead);
		if (get_time() >= philo->time_to_die)
			philo->table->is_dead = philo->id + 1;
		if (philo->table->is_dead || philo->remains_eat == 0)
		{
			pthread_mutex_unlock(&philo->table->mut_is_dead);
			if (philo->state == EAT)
			{
				pthread_mutex_unlock(philo->table->forks + philo->fork_r);
				pthread_mutex_unlock(philo->table->forks + philo->fork_l);
			}
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->mut_is_dead);
		do_action(philo);
		usleep(750);
	}
	return (NULL);
}
