/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:17:55 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/11 17:25:27 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	free_table(t_table *table)
{
	pthread_mutex_destroy(&table->mut_display);
	pthread_mutex_destroy(&table->mut_is_dead);
	pthread_mutex_destroy(&table->mut_start);
	free(table->forks);
	free(table);
}

void	free_philos(t_philo *philos)
{
	int	i;

	i = -1;
	//while (philos[++i].id != -1)
	//	pthread_mutex_destroy(&philos[i].mutex);
	while (philos[++i].id != -1)
		pthread_mutex_destroy(&philos[i].mut_time_to_die);
	free(philos);
}


static int	*init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(*table->forks) * table->nb_philo);
	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_init(table->forks + i, NULL);
	return (0);
}

// NEED TO FREEE AFTER ALL
t_table	*init_table(int eat_limit, char **args)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->nb_philo = ft_atoi(args[1]);
	init_forks(table);
	table->is_dead = 0;
	table->time_to_die = ft_atoi(args[2]);
	table->time_to_eat = ft_atoi(args[3]);
	table->time_to_sleep = ft_atoi(args[4]);
	table->time_to_think = table->time_to_eat - table->time_to_sleep + 2;
	//table->start_time = get_time();
	table->start_time = get_time() + 30;
	if (eat_limit)
		table->nb_must_eat = ft_atoi(args[5]);
	else
		table->nb_must_eat = -42;
	
	pthread_mutex_init(&table->mut_display, NULL);
	pthread_mutex_init(&table->mut_is_dead, NULL);
	pthread_mutex_init(&table->mut_start, NULL);
	table->nb_loaded = 0;
	return (table);
}

t_philo	*init_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * (table->nb_philo + 1));
	i = -1;
	while (++i < table->nb_philo)
	{
		philos[i].table = table;
		philos[i].id = i;
		philos[i].state = -1;
		//philos[i].time_to_die = get_time() + table->time_to_die;
		philos[i].time_to_die = 0;
		philos[i].remains_eat = table->nb_must_eat;
		philos[i].fork_r = i;
		if (i == 0)
			philos[i].fork_l = table->nb_philo - 1;
		else
			philos[i].fork_l = i - 1;

		//philos[i].fork_r = i + 1 % table->nb_philo;
		//philos[i].fork_l = i % table->nb_philo;
		pthread_mutex_init(&philos[i].mut_time_to_die, NULL);

		if (pthread_create(&philos[i].thread, NULL, routine, philos + i))
			return (printf("failed to create thread !\n"), NULL);
	}
	philos[i].id = -1;
	return (philos);
}
