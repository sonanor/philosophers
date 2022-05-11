/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:36:44 by adratini          #+#    #+#             */
/*   Updated: 2022/05/08 19:36:45 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	execute_program(t_philo *philo)
{
	if (!mutex_dead_flag(philo->table))
	{
		if (!philo_eat(philo))
			return (0);
		if (philo->table->input.count_eat != mutex_times_ate(philo))
		{
			if (!philo_sleep(philo))
				return (0);
			if (!philo_print(philo, THINK))
				return (0);
		}
		return (1);
	}
	return (0);
}

void	*check_philo(void *args)
{
	t_table	*table;
	int		i;

	table = (t_table *)args;
	i = 0;
	while (!mutex_dead_flag(table))
	{
		if (table->input.count_eat && all_fed(table))
			break ;
		is_dead(table, &i);
	}
	return (NULL);
}

void	*philo(void *args)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)args;
	table = philo->table;
	if (philo->index % 2 == 0)
		usleep(1500);
	while (!mutex_dead_flag(table))
	{
		if (table->input.count_eat && mutex_times_ate(philo) == table->input \
				.count_eat)
			break ;
		if (!execute_program(philo))
			break ;
	}
	return (NULL);
}

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_num)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(table->master, NULL) != 0)
		return (0);
	return (1);
}

int	init_threads(t_table *table)
{
	int	i;

	i = 0;
	table->is_dead_flg = 0;
	table->all_fed = 0;
	while (i < table->input.philo_num)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo, \
		&table->philos[i]) != 0)
			return (0);
		pthread_mutex_lock(&table->ate);
		table->philos[i].last_time_ate = table->time_start;
		pthread_mutex_unlock(&table->ate);
		i++;
	}
	if (pthread_create(&table->master, NULL, &check_philo, table) != 0)
		return (0);
	if (!join_threads(table))
		return (0);
	return (1);
}
