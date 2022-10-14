/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:16:39 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/14 17:16:40 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static long	ft_latoi(const char *str)
{
	int			signe;
	long		nbr;

	nbr = 0;
	signe = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (str[1] == '+' || str[1] == '-')
			return (0);
		if (*str++ == '-')
			signe = -1;
	}
	while (*str >= '0' && *str <= '9')
		nbr = (nbr * 10) + (*str++ - '0');
	return (nbr * signe);
}

int	is_there_ouflow(char **valstr)
{
	while (*valstr)
	{
		if (ft_latoi(*valstr) < INT_MIN || ft_latoi(*valstr) > INT_MAX
			|| ft_strlen(*valstr) > 11)
			return (1);
		valstr++;
	}
	return (0);
}
