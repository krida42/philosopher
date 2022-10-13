/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:53:41 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/13 20:52:15 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	describe_table(t_table *table, t_philo	*philos)
{
	const int	i = 0;

	printf("id: %d\n", philos[i].id);
	printf("state: %d\n", philos[i].state);
	printf("time to die : %ld\n", philos[i].time_to_die);
	printf("time to eat : %ld\n", philos[i].time_to_eat);
	printf("time to sleep : %ld\n", philos[i].time_to_sleep);
	printf("nb times : %ld\n", philos[i].time_to_eat);
	printf("time now in ms : %lu\n", get_time());
	fflush(stdout);
	(void) philos;
	(void) table;
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philos;
	int		i;

	puts("- - - - - - - - - - - - - - - - - - -\n");
	if (argc != 5 && argc != 6)
		return (printf(RED"Pas le bon nombre d'argument !\n"WHITE));
	if (iserr_args(argv + 1))
		return (1);
	table = init_table(argc == 6, argv);
	philos = init_philos(table);
	if (philos)
		table->philos = philos;
	if (!philos || start_monitor(table))
		return (2);
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (printf(RED"Cant't join thread\n"WHITE));
	}
	describe_end(philos);
	free_philos(philos);
	free_table(table);
	return (0);
}
