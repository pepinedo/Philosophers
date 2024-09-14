/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:48:44 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/13 17:43:18 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	p_write(t_philo **philo, char *str)
{
	unsigned long	time;

	if (pthread_mutex_lock(&(*philo)->data->write)) //bloquear para uso exclusivo del orquestador
		return (1);
	time = get_time() - (*philo)->data->start; // calcular cuanto ha tardado en morir
	printf(YELLOW"%lu"RESET" %d %s\n", time, (*philo)->id, str); 
	pthread_mutex_unlock(&(*philo)->data->write); // desbloquar
	return (0);
}

void	finish_write(int death, t_philo *philo, int max_eat)
{
	if (death == 1)
	{
		if (p_write(&philo, RED"DIED."RESET)) // si falla es que ha habido un error en el mutex
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