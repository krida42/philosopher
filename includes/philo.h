/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:33:58 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/20 03:42:41 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ULONG unsigned long
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define GRAY "\033[0;37m"
# define WHITE "\033[0m"
# define RED "\033[1;31m"

typedef struct s_table {
	int		nb_philo;
	int		*forks;
	int		is_death;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_must_eat;
}	t_table;

typedef struct s_philo {
	int			id;
	pthread_t	thread;
	int			state;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			remains_eat;
	int			fork_r;
	int			fork_l;
}	t_philo;

t_table	*init_table(int eat_limit, char **args);
t_philo	*init_philos(t_table *table);

void	free_table(t_table *table);
void	free_philos(t_philo *philos);

ULONG	get_time(void);
void	my_sleep(ULONG ms);

int		ft_atoi(const char *s);

void	*routine(void *philo);
void	check_death(t_philo *philos, t_table *table);

void	blue(void);
void	purple(void);
void	gray(void);
void	white(void);
void	red(void);
#endif 
