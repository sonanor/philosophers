/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adratini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:35:39 by adratini          #+#    #+#             */
/*   Updated: 2022/05/08 19:35:41 by adratini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->table->forks[philo->left_fork]) != 0)
		return (0);
	if (philo->table->input.philo_num > 1)
		if (pthread_mutex_unlock(&philo->table->forks[philo->right_fork]) != 0)
			return (0);
	return (1);
}

int	grab_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->forks[philo->left_fork]) != 0)
		return (0);
	if (!philo_print(philo, FORK))
		return (0);
	if (philo->table->input.philo_num == 1)
	{
		ft_usleep(philo->table->input.time_die + 2000);
		return (1);
	}
	if (pthread_mutex_lock(&philo->table->forks[philo->right_fork]) != 0)
		return (0);
	if (!philo_print(philo, FORK))
		return (0);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	if (!grab_fork(philo))
		return (0);
	if (!philo_print(philo, EAT))
		return (0);
	pthread_mutex_lock(&philo->table->ate);
	philo->last_time_ate = get_time();
	pthread_mutex_unlock(&philo->table->ate);
	ft_usleep(philo->table->input.time_eat);
	if (!drop_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->table->times_ate);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->table->times_ate);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (!philo_print(philo, SLEEP))
		return (0);
	ft_usleep(philo->table->input.time_sleep);
	return (1);
}
