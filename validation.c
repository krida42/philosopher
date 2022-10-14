/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:16:48 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/14 17:19:38 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	is_only_nbrs(char **valstr)
{
	int	i;

	while (*valstr)
	{
		i = 0;
		while ((*valstr)[i])
		{
			if (((*valstr)[i] == '-' || (*valstr)[i] == '+') && (*valstr)[1]
					&& i == 0 && ++i)
				continue ;
			if (!ft_isdigit((*valstr)[i++]))
				return (0);
		}
		valstr++;
	}
	return (1);
}

int	iserr_args(char **argv)
{
	int	j;
	int	nb;

	if (!is_only_nbrs(argv))
	{
		printf(RED"Seul les nombres sont acceptes\n"WHITE);
		return (1);
	}
	if (is_there_ouflow(argv) && (printf(RED"Il y a un overflow\n"WHITE) || 1))
		return (1);
	j = -1;
	while (argv[++j])
	{
		nb = ft_atoi(argv[j]);
		if ((j == 0 && (nb > 10000 || nb < 1)) || nb < 0)
		{
			if (j == 0)
				printf(RED"Nombre de philo invalide\n");
			else
				printf(RED"Argument invalide\n");
			return (1);
		}
	}
	return (0);
}
