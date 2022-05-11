/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:36:28 by adratini          #+#    #+#             */
/*   Updated: 2022/05/08 19:36:29 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	table.time_start = get_time();
	if (!parse_input(argc, argv, &table))
		return (1);
	if (!init_mutexes(&table))
	{
		free_all(&table);
		return (2);
	}
	if (!init_threads(&table))
	{
		free_all(&table);
		return (3);
	}
	if (!finish_program(&table))
	{
		free_all(&table); 
		return (4);
	}
	return (0);
}
