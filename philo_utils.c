/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:53:16 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/21 17:58:09 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
