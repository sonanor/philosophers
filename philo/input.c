/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:35:59 by adratini          #+#    #+#             */
/*   Updated: 2022/05/08 19:36:00 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_table *table, int i, int j)
{
	table->philos[i].index = i + 1;
	table->philos[i].left_fork = i;
	table->philos[i].right_fork = j;
	table->philos[i].last_time_ate = 0;
	table->philos[i].times_ate = 0;
	table->philos[i].table = table;
}

int	init_philos(t_table *table)
{
	int	i;
	int	j;

	table->philos = malloc(sizeof(t_philo) * (table->input.philo_num));
	if (!table->philos)
		return (0);
	i = 0;
	j = 1;
	while (i < table->input.philo_num - 1)
	{
		init_philo(table, i, j);
		i++;
		j++;
	}
	j = 0;
	init_philo(table, i, j);
	return (1);
}

int	parse_input(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (0);
	table->input.philo_num = philo_atoi(argv[1]);
	table->input.time_die = philo_atoi(argv[2]) * 1000;
	table->input.time_eat = philo_atoi(argv[3]) * 1000;
	table->input.time_sleep = philo_atoi(argv[4]) * 1000;
	if (argc == 6)
		table->input.count_eat = philo_atoi(argv[5]);
	else
		table->input.count_eat = 0;
	if (!table->input.philo_num || !table->input.time_die || \
		!table->input.time_eat || !table->input.time_sleep || \
		(argc == 6 && !table->input.count_eat))
		return (0);
	if (!init_philos(table))
		return (0);
	return (1);
}
