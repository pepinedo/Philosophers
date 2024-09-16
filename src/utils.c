/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:39:13 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/16 13:47:32 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_update(t_philo **philo)
{
	(*philo)->eat_times++;
	(*philo)->die_time = get_time() + (*philo)->data->die_time
		- (*philo)->data->start;
}

void	free_forks(t_philo **philo)
{
	if ((*philo)->data->n_philos != 1)
	{
		pthread_mutex_unlock((*philo)->l_fork);
		pthread_mutex_unlock((*philo)->r_fork);
	}
	else
		((*philo)->data->death = 1);
}

long	get_time(void)
{
	struct timeval	time;
	long			time_ms;

	if (gettimeofday(&time, NULL))
		return (0);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

long	ft_usleep(int time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	writer(t_philo **philo, char *str)
{
	unsigned long	time;

	if (pthread_mutex_lock(&(*philo)->data->write))
		return (1);
	time = get_time() - (*philo)->data->start;
	printf(YELLOW"%lu"RESET" %d %s\n", time, (*philo)->id, str);
	pthread_mutex_unlock(&(*philo)->data->write);
	return (0);
}
