/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:51:45 by ppinedo-          #+#    #+#             */
/*   Updated: 2024/09/16 14:04:52 by ppinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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
	pthread_t		orchestrator;
	int				n_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				full;
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
	uint64_t		die_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

//--- FUNCTIONS ----
bool		check_args(int ac, char **av, t_data **data);
bool		check_number_of_args(int ac, char **av);
bool		check_times(int ac, char **av);
bool		check_special_cases(int ac, char **av);

void		init_data(t_data **data, int ac, char **av);
void		init_mutex(t_data *data);
void		init_forks(pthread_mutex_t **forks, int size);
void		init_philosophers(t_philo **philosopher, t_data **data);

int			algorithm(t_data **data);
void		*orchestrator(void *arg);
void		death_checker(t_data *data, t_philo **current_philo);
void		finish_write(int death, t_philo *philo, int max_eat);
void		*actions(void *arg);
int			take_forks(t_philo **philo);
int			even_philo(t_philo **philo);
int			odd_philo(t_philo **philo);
int			eat(t_philo **philo);
void		philo_update(t_philo **philo);

void		free_all(t_data **data);
void		end_mutex(t_data **data);

//----- UTILS ------
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
int			ft_isdigit(int c);
int			arg_is_number(char *arg, int i);
long int	ft_atoi(char *str);
long		get_time(void);
int			writer(t_philo **philo, char *str);
long		ft_usleep(int time);
void		free_forks(t_philo **philo);
long		get_time(void);

#endif