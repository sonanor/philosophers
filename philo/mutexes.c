/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:36:17 by adratini          #+#    #+#             */
/*   Updated: 2022/05/08 19:36:18 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_num)
	{
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_destroy(&table->print) != 0)
		return (0);
	if (pthread_mutex_destroy(&table->dead) != 0)
		return (0);
	if (pthread_mutex_destroy(&table->ate) != 0)
		return (0);
	if (pthread_mutex_destroy(&table->times_ate) != 0)
		return (0);
	free_all(table);
	return (1);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->forks = (pthread_mutex_t *) malloc(sizeof (pthread_mutex_t) * \
			table->input.philo_num);
	if (!table->forks)
	{
		free(table->philos);
		return (0);
	}
	while (i < table->input.philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], 0) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&table->print, 0) != 0)
		return (0);
	if (pthread_mutex_init(&table->dead, 0) != 0)
		return (0);
	if (pthread_mutex_init(&table->ate, 0) != 0)
		return (0);
	if (pthread_mutex_init(&table->times_ate, 0) != 0)
		return (0);
	return (1);
}

int	mutex_dead_flag(t_table *table)
{
	pthread_mutex_lock(&table->dead);
	if (table->is_dead_flg)
	{
		pthread_mutex_unlock(&table->dead);
		return (1);
	}
	pthread_mutex_unlock(&table->dead);
	return (0);
}

int	mutex_times_ate(t_philo *philo)
{
	int	times_ate;

	pthread_mutex_lock(&philo->table->times_ate);
	times_ate = philo->times_ate;
	pthread_mutex_unlock(&philo->table->times_ate);
	return (times_ate);
}
