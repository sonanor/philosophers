/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:56:36 by adratini          #+#    #+#             */
/*   Updated: 2022/04/03 17:56:37 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK 	"has taken a fork"
# define EAT		"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIED		"died"

typedef struct s_input
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				count_eat;
}	t_input;

typedef struct s_philo
{
	int				index;
	int				times_ate;
	long long		last_time_ate;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				all_fed;
	int				is_dead_flg;
	long long		time_start;
	t_input			input;
	pthread_t		master;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	ate;
	pthread_mutex_t	times_ate;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

int			philo_atoi(const char *str);
long long	get_time(void);
long long	get_time_delta(long long time);
int			mutex_times_ate(t_philo *philo);
int			mutex_dead_flag(t_table *table);
int			parse_input(int argc, char **argv, t_table *table);
int			init_mutexes(t_table *table);
int			init_threads(t_table *table);
int			philo_print(t_philo *philo, char *action);
int			philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
void		free_all(t_table *table);
int			finish_program(t_table *table);
void		is_dead(t_table *table, int *i);
int			all_fed(t_table *table);
void		ft_usleep(int time);

#endif
