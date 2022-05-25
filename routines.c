/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:48:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/25 01:58:55 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	move_fork(t_philo *philo, int take)
{
	const t_table	*table = philo->table;
	const ULONG		timestamp = get_time() - philo->table->start_time;

	pthread_mutex_lock(&philo->table->mut_display);
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
	else if (state == EAT)
	{
		philo->time_to_eat = get_time() + philo->table->time_to_eat;
		philo->time_to_die += philo->table->time_to_die;
		printf("%lu %d is eating\n", timestamp, philo->id + 1);
	}
	else if (state == SLEEP)
	{
		philo->time_to_sleep = get_time() + philo->table->time_to_sleep;
		printf("%lu %d is sleeping\n", timestamp, philo->id + 1);
	}
	philo->state = state;
	pthread_mutex_unlock(&philo->table->mut_display);
}

static void	first_action(t_philo *philo)
{
	const int	is_odd = philo->id % 2;

	if (is_odd)
		move_fork(philo, 1);
	set_state(philo, is_odd);
}

static void	do_action(t_philo *philo)
{
	if (philo->state == -1)
		first_action(philo);
	else if (philo->state == THINK && philo->table->nb_philo > 1)
	{
		if (forks_available(philo))
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
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		if (get_time() >= philo->time_to_die)
			philo->table->is_dead = 1;
		if (philo->table->is_dead || philo->remains_eat == 0)
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
