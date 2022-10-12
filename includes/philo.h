/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:33:58 by kisikaya          #+#    #+#             */
/*   Updated: 2022/10/12 19:51:12 by kisikaya         ###   ########.fr       */
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
# define GREEN "\001\033[1;32m\002"

# define THINK 0
# define EAT 1
# define SLEEP 2

typedef struct s_table {
	int				nb_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mut_is_dead;
	int				is_dead;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			nb_must_eat;
	ULONG			start_time;
	pthread_mutex_t	mut_display;
	pthread_mutex_t	mut_start;
	int				nb_loaded;
	struct s_philo	*philos;
}	t_table;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	int				state;
	ULONG			time_to_die;
	ULONG			time_to_eat;
	ULONG			time_to_sleep;
	ULONG			time_to_think;
	ULONG			remains_eat;
	int				fork_r;
	int				fork_l;
	struct s_table	*table;
	pthread_mutex_t	mut_time_to_die;
}	t_philo;

t_table	*init_table(int eat_limit, char **args);
t_philo	*init_philos(t_table *table);

void	free_table(t_table *table);
void	free_philos(t_philo *philos);

ULONG	get_time(void);
void	my_sleep(ULONG ms);

int		ft_atoi(const char *s);
void	print_status(char *fmt, ULONG timestamp, int id, pthread_mutex_t *mut);

void	*routine(void *philo);

void	describe_end(t_philo *philos);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);
int		forks_available(t_philo *philo);

int		start_monitor(t_table *table);

void	blue(void);
void	purple(void);
void	gray(void);
void	white(void);
void	red(void);
#endif 
