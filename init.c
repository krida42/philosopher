/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:17:55 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/19 21:52:17 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	free(table->forks);
	free(table);
}

void	free_philos(t_philo *philos)
{
	free(philos);
}

static int	*init_forks(int n)
{
	int	*forks;

	forks = malloc(sizeof(int) * n);
	while (n--)
		forks[n] = 1;
	return (forks);
}

// NEED TO FREEE AFTER ALL
t_table	*init_table(int eat_limit, char **args)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->nb_philo = ft_atoi(args[1]);
	table->forks = init_forks(table->nb_philo);
	table->is_death = 0;
	table->time_to_die = ft_atoi(args[2]);
	table->time_to_eat = ft_atoi(args[3]);
	table->time_to_sleep = ft_atoi(args[4]);
	if (eat_limit)
		table->nb_must_eat = ft_atoi(args[5]);
	else
		table->nb_must_eat = -42;
	return (table);
}

t_philo	*init_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * (table->nb_philo));
	i = -1;
	while (++i < table->nb_philo)
	{
		philos[i].id = i;
		philos[i].state = 0;
		philos[i].time_to_die = table->time_to_die;
		philos[i].time_to_eat = table->time_to_eat;
		philos[i].time_to_sleep = table->time_to_sleep;
		philos[i].remains_eat = table->nb_must_eat;
		philos[i].fork_r = i;
		if (i == 0)
			philos[i].fork_l = table->nb_philo - 1;
		else
			philos[i].fork_l = i - 1;
	}
	return (philos);
}
