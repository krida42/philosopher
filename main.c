/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:53:41 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/19 21:52:41 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	describe_table(t_table *table, t_philo	*philos)
{
	int	i = 2;
	printf("id: %d\n", philos[i].id);
	printf("time to die : %ld\n", philos[i].time_to_die);
	printf("time to eat : %ld\n", philos[i].time_to_eat);
	printf("time to sleep : %ld\n", philos[i].time_to_sleep);
	printf("nb times : %ld\n", philos[i].time_to_eat);
	(void) philos;
	(void) table;
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (puts("Pas le bon nombre d'argument !"));
	table = init_table(argc == 6, argv);
	philos = init_philos(table);
	describe_table(table, philos);
	free_philos(philos);
	free_table(table);
	return (0);
}
