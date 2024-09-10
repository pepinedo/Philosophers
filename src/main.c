/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:42:42 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/10 14:34:49 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!checks(ac, av, &data))
		return (0);
	if (ac >= 6 && (ft_atoi(av[5]) == 0))
	{
		printf("Philosophers has eaten 0 times\n");
		free(data);
		return (0);
	}
	init_data(&data, ac, av);
//-----------------------------------------------------------------------------		
	// thread_init(&data);
	// finish_philo(&data);
	return (0);
}
