/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:26:32 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/16 14:04:20 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	odd_philo(t_philo **philo)
{
	if (pthread_mutex_lock((*philo)->l_fork))
		return (1);
	if ((*philo)->data->death != 0)
	{
		pthread_mutex_unlock((*philo)->l_fork);
		return (0);
	}
	if ((*philo)->data->n_philos == 1)
		ft_usleep((*philo)->data->die_time + 1);
	if (writer(philo, "has taken left fork"))
		return (1);
	if ((*philo)->data->n_philos >= 1)
	{
		if (pthread_mutex_lock((*philo)->r_fork))
			return (1);
	}
	if ((*philo)->data->death != 0)
	{
		pthread_mutex_unlock((*philo)->l_fork);
		pthread_mutex_unlock((*philo)->r_fork);
		return (0);
	}
	if (writer(philo, "has taken rigth fork"))
		return (1);
	return (0);
}

int	even_philo(t_philo **philo)
{
	if (pthread_mutex_lock((*philo)->r_fork))
		return (1);
	if ((*philo)->data->death != 0)
	{
		pthread_mutex_unlock((*philo)->r_fork);
		return (0);
	}
	if (writer(philo, "has taken right fork"))
		return (1);
	if (pthread_mutex_lock((*philo)->l_fork))
		return (1);
	if ((*philo)->data->death != 0)
	{
		pthread_mutex_unlock((*philo)->r_fork);
		pthread_mutex_unlock((*philo)->l_fork);
		return (0);
	}
	if (writer(philo, "has taken left fork"))
		return (1);
	return (0);
}

int	take_forks(t_philo **philo)
{
	if ((*philo)->data->n_philos == 1)
	{
		pthread_mutex_lock((*philo)->l_fork);
		if (writer(philo, "has taken left fork"))
			return (1);
		ft_usleep((*philo)->data->die_time);
		pthread_mutex_unlock((*philo)->l_fork);
		(*philo)->data->death = 1;
		return (0);
	}
	if ((*philo)->data->death != 0)
		return (0);
	if ((*philo)->id % 2 == 0)
	{
		if (even_philo(philo))
			return (1);
	}
	else
	{
		if (odd_philo(philo))
			return (1);
	}
	return (0);
}

int	eat(t_philo **philo)
{
	if ((*philo)->data->death != 0)
	{
		free_forks(philo);
		return (0);
	}
	philo_update(philo);
	if ((*philo)->data->death != 0)
	{
		free_forks(philo);
		return (0);
	}
	if (writer(philo, GREEN"is eating"RESET))
		return (1);
	free_forks(philo);
	if ((*philo)->data->death != 0)
		return (0);
	if (writer(philo, BLUE"is sleeping"RESET))
		return (1);
	usleep((*philo)->data->sleep_time * 1000);
	if ((*philo)->data->death != 0)
		return (0);
	if (writer(philo, YELLOW"is thinking"RESET))
		return (1);
	return (0);
}
