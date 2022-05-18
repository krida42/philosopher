/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:33:58 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/18 21:34:55 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_table {
	long	nb_philo;
	int		*forks;
	int		is_death;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_must_eat;
}	t_table;

typedef struct s_philo {
	int		id;
	int		state;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		remains_eat;
	int		fork_r;
	int		fork_l;
}	t_philo;

int	ft_atoi(const char *s);
#endif 
