/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:51:45 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/10 13:19:10 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <inttypes.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\033[37m"
# define BOLD		"\033[1m"
# define RESET		"\x1b[0m"
# define CLEAR		"\033[2J"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	pthread_t		*thread;
	pthread_t		super;
	int				diners;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat;
	int				death;
	uint64_t		start;
	t_philo			*philosopher;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	bool			eating;
	int				eat_times;
	uint64_t		time_to_die;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

#endif