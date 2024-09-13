/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:26:32 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/13 13:54:32 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	odd_philo(t_philo **philo)
{
	if (pthread_mutex_lock((*philo)->l_fork)) //intenta coger el IZQUIERDO
		return (1);
	if ((*philo)->data->death != 0) // si alguno muere, desbloquea el izquierdo
	{
		pthread_mutex_unlock((*philo)->l_fork);
		return (0);
	}
	if ((*philo)->data->diners == 1) // ????
		ft_usleep((*philo)->data->die_time + 1);
	if (writer(philo, "has taken left fork"))   //printf
		return (1);
	if ((*philo)->data->diners >= 1) // bloquea el tenedor derecho si hay mas de un philosopho
	{
		if (pthread_mutex_lock((*philo)->r_fork))
			return (1);
	}
	if ((*philo)->data->death != 0) // Si alguno ha muerto, a desbloquear
	{
		pthread_mutex_unlock((*philo)->l_fork);
		pthread_mutex_unlock((*philo)->r_fork);
		return (0);
	}
	if (writer(philo, "has taken rigth fork"))  //printf
		return (1);
	return (0);
}

int	even_philo(t_philo **philo)
{
	if (pthread_mutex_lock((*philo)->r_fork)) //primero quedarse con el tenedor DERECHO
		return (1);
	if ((*philo)->data->death != 0) // si alguien muere, desbloquea tenedor derecho
	{
		pthread_mutex_unlock((*philo)->r_fork);
		return (0);
	}
	if (writer(philo, "has taken right fork")) // si llega hasta aqui es que ha cogido el tenedor derecho
		return (1);
	if (pthread_mutex_lock((*philo)->l_fork)) // ahora el IZQUIERDO (intenta hacer lo mismo)
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
	if ((*philo)->data->death != 0)
		return (0);
	if ((*philo)->id % 2 == 0) //comprobar si es par o impar, para evitar conflictos y deadlocks.
	{
		if (even_philo(philo)) // los pares empiezan cogiendo el tenedor derecho
			return (1);
	}
	else
	{
		if (odd_philo(philo)) // los impares empeizan cogiendo el tenedor izquierdo
			return (1);
	}
	return (0);
}

int	eat(t_philo **philo)
{
	if ((*philo)->data->death != 0) //si alguno ha muerto, a soltar tenedores
	{
		free_forks(philo, 0);
		return (0);
	}
	philo_update(philo); //la comilona en si
	if ((*philo)->data->death != 0) // si alguno ha muerto, a soltar tenedores
	{
		free_forks(philo, 0);
		return (0);
	}
	if (writer(philo, GREEN"is eating"RESET))
		return (1);
	free_forks(philo, 1); // ya ha comido, asi que a soltar tenedores
	if ((*philo)->data->death != 0) // si alguno ha muerto, fuera
		return (0);
	if (writer(philo, BLUE"is sleeping"RESET)) // duerme
		return (1);
	usleep((*philo)->data->sleep_time * 1000); // duermme el hilo hasta que termine su tiempo de dormir
	if ((*philo)->data->death != 0) // si alguno ha muerto, fuera
		return (0);
	if (writer(philo, YELLOW"is thinking"RESET))
		return (1);
	return (0);
}