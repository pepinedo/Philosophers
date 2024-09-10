/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:10:28 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/10 13:09:08 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_times(int ac, char **av)
{
	bool	A;

	A = true;
	if (ac >= 2 && ft_atoi(av[1]) < 1)
	{
		printf("Error:\nThere are no Philosophers.\n");
		A = false;
	}
	if (ac >= 3 && ft_atoi(av[2]) < 1)
	{
		printf("Error:\nDie time must be greater than 0.\n");
		A = false;
	}
	if (ac >= 4 && ft_atoi(av[3]) < 1)
	{
		printf("Error:\nEat time must be greater than 0.\n");
		A = false;
	}
	if (ac >= 5 && ft_atoi(av[4]) < 1)
	{
		printf("Error:\nSleep time must be greater than 0.\n");
		A = false;
	}
	return (A);
}

bool	check_number_of_args(int ac, char **av)
{
	bool	A;

	A = true;
	if (ac < 5)
	{
		printf("Error:\nNot enough arguments.\n");
		A = false;
	}
	if (ac > 6)
	{
		printf("Error:\nTo much arguments.\n");
		A = false;
	}
	if (ac >= 6 && ft_atoi(av[5]) < 0)
	{
		printf("Error:\nThe last argument must be greater than 0.\n");
		A = false;
	}
	return (A);
}

bool	checks(int ac, char **av, t_data **data)
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
	return(true);
}