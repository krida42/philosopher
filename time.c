/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:34:33 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/20 03:04:17 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ULONG	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(ULONG ms)
{
	ULONG	start;
	ULONG	end;
	ULONG	curr;

	start = get_time();
	end = start + ms;
	curr = start;
	while (curr < end)
	{
		curr = get_time();
		usleep(100);
	}
}
