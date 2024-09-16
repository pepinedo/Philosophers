/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:48:44 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/16 12:53:16 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	finish_write(int death, t_philo *philo, int max_eat)
{
	if (death == 1)
	{
		if (writer(&philo, RED"DIED."RESET)) // si falla es que ha habido un error en el mutex
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
	while (i < data->n_philos && data->death == 0) //mientras que no haya ninguno muerto (data->death == 1)
	{
		current_time = get_time() - data->start; //calculas cuanto tiempo lleva sin comer
		(*current_philo) = &data->philosopher[i];
		if (current_time > (*current_philo)->die_time) //si el tiempo sin comer es mayor al que aguanta sin comer, fin
		{
			data->death = 1;
			break ;
		}
		if ((*current_philo)->eat_times >= data->full) // si ha comido lo suficiente, al siguiente
			j++;
		if (j == data->n_philos && data->full > 0) // si todos han comido, fin
		{
			data->death = 2; //caso de todos han comido
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
	// if (pthread_mutex_lock(&data->lock))
	// {
	// 	data->death = 3; // caso de error del mutex
	// 	return (NULL);
	// }
	while (data->death == 0) // mientras que ningun filosofo este muerto, ejecuta el comprobador de muertos
		death_checker(data, &check_dead);  
	// pthread_mutex_unlock(&data->lock);
	j = 0;
	while (j < data->n_philos) // esperar a que todos los filosofos terminen
	{
		pthread_join(data->thread[j], NULL);
		j++;
	}
	finish_write(data->death, check_dead, data->full); // escribir el final
	return (NULL);
}