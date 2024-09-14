/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:10:28 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/14 13:12:16 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_times(int ac, char **av)
{
	bool	return_value;

	return_value = true;
	if (ac >= 2 && ft_atoi(av[1]) < 1)
	{
		printf(RED"Error:\nThere are no Philosophers.\n"RESET);
		return_value = false;
	}
	if (ac >= 3 && ft_atoi(av[2]) < 1)
	{
		printf(RED"Error:\nDie time must be greater than 0.\n"RESET);
		return_value = false;
	}
	if (ac >= 4 && ft_atoi(av[3]) < 1)
	{
		printf(RED"Error:\nEat time must be greater than 0.\n"RESET);
		return_value = false;
	}
	if (ac >= 5 && ft_atoi(av[4]) < 1)
	{
		printf(RED"Error:\nSleep time must be greater than 0.\n"RESET);
		return_value = false;
	}
	return (return_value);
}

bool	check_number_of_args(int ac, char **av)
{
	bool	return_value;

	return_value = true;
	if (ac < 5)
	{
		printf(RED"Error:\nNot enough arguments.\n"RESET);
		return_value = false;
	}
	if (ac > 6)
	{
		printf(RED"Error:\nTo much arguments.\n"RESET);
		return_value = false;
	}
	if (ac >= 6 && ft_atoi(av[5]) < 0)
	{
		printf(RED"Error:\nThe last argument must be greater than 0.\n"RESET);
		return_value = false;
	}
	return (return_value);
}

bool	check_args(int ac, char **av, t_data **data)
{
	if (!check_number_of_args(ac, av))
	{
		free(*data);
		return (false);
	}
	if (!check_times(ac, av))
	{
		free(*data);
		return (false);
	}
	if (ac >= 6 && (ft_atoi(av[5]) == 0))
	{
		printf("Philosophers has eaten 0 times\n");
		free(*data);
		return (false);
	}
	return (true);
}
