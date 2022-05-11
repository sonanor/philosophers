/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:35:49 by adratini          #+#    #+#             */
/*   Updated: 2022/05/08 19:35:51 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_table *table, int *i)
{
	long long	time_hungry;
	long long	last_time_ate;

	if (*i == table->input.philo_num)
		*i = 0;
	pthread_mutex_lock(&table->ate);
	last_time_ate = table->philos[*i].last_time_ate;
	pthread_mutex_unlock(&table->ate);
	time_hungry = get_time_delta(last_time_ate) * 1000;
	if (time_hungry > table->input.time_die)
	{
		philo_print(&table->philos[*i], DIED);
		pthread_mutex_lock(&table->dead);
		table->is_dead_flg = 1;
		pthread_mutex_unlock(&table->dead);
	}
	(*i)++;
}

int	all_fed(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_num)
	{
		if (mutex_times_ate(&table->philos[i]) == table->input.count_eat)
			table->all_fed++;
		i++;
	}
	return (table->all_fed == table->input.count_eat);
}

int	philo_print(t_philo *philo, char *action)
{
	long long	time;

	if (!mutex_dead_flag(philo->table))
	{
		time = get_time_delta(philo->table->time_start);
		if (pthread_mutex_lock(&philo->table->print) != 0)
			return (0);
		if (mutex_dead_flag(philo->table))
		{
			pthread_mutex_unlock(&philo->table->print);
			return (0);
		}
		else
			printf("%lld\t%d\t %s\n", time, philo->index, action);
		if (pthread_mutex_unlock(&philo->table->print) != 0)
			return (0);
	}
	return (1);
}
