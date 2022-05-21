/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:48:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/21 22:03:17 by kisikaya         ###   ########.fr       */
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
			exit (printf(RED "trying to get forks somehere theres isnt fork" WHITE));
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
		printf("%lu %d is thinking\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->table->mut_display);
}

static void	do_action(t_philo *philo)
{
	int	is_odd;

	pthread_mutex_lock(&philo->mutex);
	is_odd = philo->id % 2;
	//philo->time_to_die--;
	if (philo->state == -1)
	{
		if (is_odd)
			move_fork(philo, 1);
		set_state(philo, is_odd);
	}

	pthread_mutex_unlock(&philo->mutex);
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = philo_p;

	pthread_mutex_lock(&philo->table->mut_display);
	printf("coucou, je suis philo: %d\n", philo->id);
	pthread_mutex_unlock(&philo->table->mut_display);
	while (1)
	{
		//const ULONG	time = get_time() / 1000 ;
		//const ULONG	time2 = get_time() % 1000;

		/*
		pthread_mutex_lock(&philo->table->mut_display);
		printf(BLUE "Time: %lu |  %lu   philos:%d, has spoken\n" WHITE, time,time2 , philo->id + 1);
		pthread_mutex_unlock(&philo->table->mut_display);
*/

		pthread_mutex_lock(&philo->table->mutex);
		if (philo->time_to_die <= 0)
			philo->table->is_dead = 1;
		if (philo->table->is_dead)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->mutex);

		do_action(philo);
		my_sleep(1);
	}
	return (NULL);
}

