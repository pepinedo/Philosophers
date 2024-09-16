/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:48:44 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/16 13:49:11 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	finish_write(int death, t_philo *philo, int max_eat)
{
	if (death == 1)
	{
		if (writer(&philo, RED"DIED."RESET))
		{
			death = 3;
			philo->data->death = 3;
		}
	}
	if (death == 2)
		printf(GREEN"The philosophers has eaten %d times. 🍾\n"RESET, max_eat);
	if (death == 3)
		printf(RED"ERROR:\nMutex failure.\n"RESET);
}

void	death_checker(t_data *data, t_philo **current_philo)
{
	int			i;
	int			j;
	uint64_t	current_time;

	i = 0;
	j = 0;
	while (i < data->n_philos && data->death == 0)
	{
		current_time = get_time() - data->start;
		(*current_philo) = &data->philosopher[i];
		if (current_time > (*current_philo)->die_time)
		{
			data->death = 1;
			break ;
		}
		if ((*current_philo)->eat_times >= data->full)
			j++;
		if (j == data->n_philos && data->full > 0)
		{
			data->death = 2;
			break ;
		}
		i++;
	}
}

void	*orchestrator(void *arg)
{
	t_data		*data;
	t_philo		*check_dead;
	int			j;

	data = (t_data *)arg;
	check_dead = NULL;
	if (pthread_mutex_lock(&data->lock))
	{
		data->death = 3;
		return (NULL);
	}
	while (data->death == 0)
		death_checker(data, &check_dead);
	pthread_mutex_unlock(&data->lock);
	j = 0;
	while (j < data->n_philos)
	{
		pthread_join(data->thread[j], NULL);
		j++;
	}
	finish_write(data->death, check_dead, data->full);
	return (NULL);
}
