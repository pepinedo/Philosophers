/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:01:13 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/11 19:42:53 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void	check_death(t_data *data, t_philo **current_philo)
// {
// 	int			i;
// 	int			j;
// 	uint64_t	now;

// 	i = 0;
// 	j = 0;
// 	while (i < data->number_of_philo && data->death == 0)
// 	{
// 		now = get_time() - data->start;
// 		(*current_philo) = &data->philosopher[i];
// 		if (now > (*current_philo)->time_to_die)
// 		{
// 			data->death = 1;
// 			break ;
// 		}
// 		if ((*current_philo)->eat_times >= data->max_eat)
// 			j++;
// 		if (j == data->number_of_philo && data->max_eat > 0)
// 		{
// 			data->death = 2;
// 			break ;
// 		}
// 		i++;
// 	}
// }

void	*master(void *arg)
{
	t_data		*data;
	uint64_t	time;
	t_philo		*check_dead;
	int			j;

	data = (t_data *)arg;
	check_dead = NULL;
	if (pthread_mutex_lock(&data->lock))
	{
		data->death = 3; // <------- ?????
		return (NULL);
	}
	while (data->death == 0)
		check_death(data, &check_dead); //   <----
//--------------------------------------------------------------
	pthread_mutex_unlock(&data->lock);
	j = 0;
	while (j < data->diners)
	{
		pthread_join(data->thread[j], NULL);
		j++;
	}
	finish_write(data->death, check_dead, data->max_eat);
	return (NULL);
}

int	thread_init(t_data **data)
{
	int			i;

	i = 0;
	if (pthread_mutex_lock(&(*data)->lock))
		return (1);
	if (pthread_create(&(*data)->master, NULL, &master, *data)) //<----
		return (1);
//--------------------------
	while (i < (*data)->diners && (*data)->death == 0)
	{
		pthread_create(&(*data)->thread[i], NULL, &actions, &(*data)->philosopher[i]);
		i++;
	}
	pthread_mutex_unlock(&(*data)->lock);
	pthread_join((*data)->master, NULL);
	return (0);
}