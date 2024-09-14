/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:01:13 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/13 17:29:33 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*orchestrator(void *arg)
{
	t_data		*data;
	t_philo		*check_dead;
	int			j;

	data = (t_data *)arg;
	check_dead = NULL;
	if (pthread_mutex_lock(&data->lock))
	{
		data->death = 3; // caso de error
		return (NULL);
	}
	while (data->death == 0) // mientras que ningun filosofo este muerto, ejecuta el comprobador de muertos
		death_checker(data, &check_dead);  
	pthread_mutex_unlock(&data->lock);
	j = 0;
	while (j < data->n_philos) // esperar a que todos los filosofos terminen
	{
		pthread_join(data->thread[j], NULL);
		j++;
	}
	finish_write(data->death, check_dead, data->full); // escribir el final
	return (NULL);
}

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(5); //utils
	philo->die_time = get_time() + philo->data->die_time - philo->data->start;
	while (philo->data->death == 0) //sus acciones (coger tenedores, comer, dormir)
	{
		if (philo->data->death == 0 && take_forks(&philo)) //coger tenedores
			philo->data->death = 3;
		if (philo->data->death == 0 && eat(&philo)) // comer
			philo->data->death = 3;
		if (philo->data->death == 0 && philo->id % 2 != 0) // si es par, breve pausa para evitar conflictos
			ft_usleep(10);
	}
	return (NULL);
}

int	algorithm(t_data **data)
{
	int			i;

	i = 0;
	if (pthread_mutex_lock(&(*data)->lock))  //para que solo un hilo pueda usar la estructura
		return (1);
	if (pthread_create(&(*data)->orchestrator, NULL, &orchestrator, *data)) // hilo del orquestador
		return (1);
	while (i < (*data)->n_philos && (*data)->death == 0)  //crea tantos hilos como filosofos se han especificado
	{
		pthread_create(&(*data)->thread[i], NULL, &actions, &(*data)->philosopher[i]);
		i++;
	}
	pthread_mutex_unlock(&(*data)->lock); //desbloqueo estandar
	pthread_join((*data)->orchestrator, NULL); //esperar a que el orquestador termine
	return (0);
}