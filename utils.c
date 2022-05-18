/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <kisikaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:31:28 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/18 21:33:43 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	signe;
	int	nbr;

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
