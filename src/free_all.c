/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:04:07 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/13 16:54:17 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	end_mutex(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->n_philos)
	{
		pthread_mutex_destroy(&(*data)->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&(*data)->lock);
	pthread_mutex_destroy(&(*data)->write);
	free((*data)->forks);
}

void	free_all(t_data **data)
{
	end_mutex(data);
	free((*data)->thread);
	free((*data)->philosopher);
	free(*data);
}