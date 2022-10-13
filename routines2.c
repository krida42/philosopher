/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:55:24 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/13 18:55:24 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_routine(t_philo *philo)
{
	while (get_time() < philo->table->start_time)
		usleep(1000);
	pthread_mutex_lock(&philo->mut_time_to_die);
	philo->time_to_die = get_time() + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->mut_time_to_die);
}
