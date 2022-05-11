/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:36:52 by adratini          #+#    #+#             */
/*   Updated: 2022/05/08 19:36:53 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (((now.tv_sec - start.tv_sec) * 1000000) + ((now.tv_usec - start
	.tv_usec)) <= time)
	{
		usleep(50);
		gettimeofday(&now, 0);
	}
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	get_time_delta(long long time)
{
	long long	delta_time;

	if (time > 0)
	{
		delta_time = get_time() - time;
		return (delta_time);
	}
	return (0);
}

int	philo_atoi(const char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (((str[i] < '0' || str[i] > '9') && str[i] != '\0') || n > 2147483647)
		return (0);
	return ((int) n);
}

void	free_all(t_table *table)
{
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}


//long long	time_diff(long long past, long long pres)
//{
//	return (pres - past);
//}
//
//void	smart_sleep(long long time, t_table *table)
//{
//	long long i;
//
//	i = get_time();
//	while (!mutex_dead_flag(table))
//	{
//		if (time_diff(i, get_time()) >= time)
//			break ;
//		usleep(50);
//	}
//}
