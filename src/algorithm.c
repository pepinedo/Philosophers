/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:01:13 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/16 14:04:26 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(5);
	while (philo->data->death == 0)
	{
		philo->die_time = get_time() + philo->data->die_time
			- philo->data->start;
		if (philo->data->death == 0 && take_forks(&philo))
			philo->data->death = 3;
		if (philo->data->death == 0 && eat(&philo))
			philo->data->death = 3;
		if (philo->data->death == 0 && philo->id % 2 != 0)
			ft_usleep(100);
	}
	return (NULL);
}

int	algorithm(t_data **data)
{
	int			i;

	i = 0;
	if (pthread_mutex_lock(&(*data)->lock))
		return (1);
	if (pthread_create(&(*data)->orchestrator, NULL, &orchestrator, *data))
		return (1);
	while (i < (*data)->n_philos && (*data)->death == 0)
	{
		pthread_create(&(*data)->thread[i], NULL,
			&actions, &(*data)->philosopher[i]);
		i++;
	}
	pthread_mutex_unlock(&(*data)->lock);
	pthread_join((*data)->orchestrator, NULL);
	return (0);
}
