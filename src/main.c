/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:42:42 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/04 13:43:18 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!parse(argc, argv, &data))
		return (0);
	if (argc >= 6 && (ft_atoi(argv[5]) == 0))
	{
		printf("Philosophers has eaten 0 times\n");
		free(data);
		return (0);
	}
	else
	{
		data_init(&data, argc, argv);
//-----------------------------------------------------------------------------		
		thread_init(&data);
	}
	finish_philo(&data);
	return (0);
}
