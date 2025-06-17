/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:50:24 by cmontaig          #+#    #+#             */
/*   Updated: 2025/06/17 14:19:30 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	int				num_of_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				num_of_meals; // optional
	int				meals_eaten;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	struct t_prog	*prog;
}					t_philo;

typedef struct s_prog
{
	long			start_time;
	bool			dead;
	int				num_of_philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_prog;

// PARSING //

int		check_input(char **av);
int		ft_atoi(char *str);

// INIT //

int		init_struct(t_prog *prog, int ac, char **av);
void	init_philo(t_prog *prog, int index, int ac, char **av);
int		init_space(t_prog *prog);
int		check_args(int ac, char **av);
int		init_mutex(t_prog *prog);

long	get_time(void);


#endif