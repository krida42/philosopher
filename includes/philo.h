/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:33:58 by kisikaya          #+#    #+#             */
/*   Updated: 2022/05/21 23:51:23 by kisikaya         ###   ########.fr       */
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
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"
# define GRAY "\001\033[0;37m\002"
# define WHITE "\001\033[0m\002"
# define RED "\001\033[1;31m\002"

typedef struct s_table {
	int				nb_philo;
	int				*forks;
	pthread_mutex_t	mutex;
	int				is_dead;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	ULONG			start_time;
	pthread_mutex_t	mut_display;
}	t_table;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	int				state;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				remains_eat;
	int				fork_r;
	int				fork_l;
	struct s_table	*table;
}	t_philo;

t_table	*init_table(int eat_limit, char **args);
t_philo	*init_philos(t_table *table);

void	free_table(t_table *table);
void	free_philos(t_philo *philos);

ULONG	get_time(void);
void	my_sleep(ULONG ms);

int		ft_atoi(const char *s);

void	*routine(void *philo);

void	describe_end(t_philo *philos);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		forks_available(t_philo *philo);

void	blue(void);
void	purple(void);
void	gray(void);
void	white(void);
void	red(void);
#endif 
