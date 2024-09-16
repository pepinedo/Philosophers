/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:41:21 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/16 13:47:41 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
	return (0);
}

int	arg_is_number(char *arg, int i)
{
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(str[i] == '+' || str[i] == '-'))
	{
		if ((str[i] == ' ') || (str[i] >= '\t' && str[i] <= '\r'))
			i++;
		else
			break ;
	}
	return (i);
}

static int	ft_negative(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(str[i] >= '0' && str[i] <= '9'))
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

long int	ft_atoi(char *str)
{
	int			i;
	int			num1;
	long int	num2;

	num2 = 0;
	i = ft_spaces(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (arg_is_number(str, i) == 0)
		return (-1);
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		else if (str[i] >= '0' && str[i] <= '9')
		{
			num1 = str[i] - '0';
			num2 = num2 * 10 + num1;
		}
		i++;
	}
	if (ft_negative(str))
		num2 = -num2;
	return (num2);
}
