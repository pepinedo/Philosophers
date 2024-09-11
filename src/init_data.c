/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:44:17 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/11 18:44:49 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time(void)
{
	struct timeval	time;
	long			miliseconds;

	if (gettimeofday(&time, NULL))
		return (0);
	miliseconds = time.tv_sec * 1000 + time.tv_usec / 1000; //to miliseconds from seconds and microseconds 
	return (miliseconds);
}

void	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
}

void	init_forks(pthread_mutex_t **forks, int size)
{
	int	i;

	i = 0;
	(*forks) = malloc(sizeof(pthread_mutex_t) * (40 * size));
	if (!(*forks))
		return ;
	while (i < size)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
}

void	init_philosophers(t_philo **philosopher, t_data **data)
{
	int	i;

	i = 0;
	*philosopher = ft_calloc((*data)->diners, sizeof(t_philo));
	if (!(*philosopher))
		return ;
	while (i < (*data)->diners)
	{
		(*philosopher)[i].data = (*data);
		(*philosopher)[i].id = i + 1;
		(*philosopher)[i].l_fork = &(*data)->forks[i];
		(*philosopher)[i].eat_times = 0;
		(*philosopher)[i].die_time = (*data)->die_time;
		if (i + 1 == (*data)->diners)
			(*philosopher)[i].r_fork = &(*data)->forks[0];
		else
			(*philosopher)[i].r_fork = &(*data)->forks[i + 1];
		i++;
	}
}

void	init_data(t_data **data, int ac, char **av)
{
	(*data)->diners = ft_atoi(av[1]);
	(*data)->die_time = ft_atoi(av[2]);
	(*data)->eat_time = ft_atoi(av[3]);
	(*data)->sleep_time = ft_atoi(av[4]);
	(*data)->death = 0;
	(*data)->start = get_time();
	(*data)->max_eat = 0;
	if (ac == 6)
		(*data)->max_eat = ft_atoi(av[5]);
		
	(*data)->thread = malloc(sizeof(pthread_t) * (*data)->diners);
	if ((*data)->thread == 0)
		return ;
	init_mutex(*data);
	init_forks(&(*data)->forks, (*data)->diners);
	if (!(*data)->diners)
		return ;
	init_philosophers(&(*data)->philosopher, data);
	if (!(*data)->philosopher)
		return ;
}