/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:43:22 by cmontaig          #+#    #+#             */
/*   Updated: 2025/06/17 12:27:58 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_struct(t_prog *prog, int ac, char **av)
{
	int i;
	
	i = 0;
	if (check_args(ac, av))
		return (1);
	prog->num_of_philos = ft_atoi(av[1]);
	prog->dead = false;
	if (init_space(prog))
		return (1);
	if (init_mutex(prog))
		return (1);
	while(i < prog->num_of_philos)
	{
		init_philo(prog, i, ac, av);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || 
		ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (1);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (1);
	return (0);
}

int	init_space(t_prog *prog)
{
	prog->philo = malloc(sizeof(t_philo) * prog->num_of_philos);
	if (!prog->philo)
		return (1);
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);
	if (!prog->forks)
	{
		free(prog->philo);
		return (1);
	}
	return (0);
}

int	init_mutex(t_prog *prog)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&prog->dead_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&prog->eat_mutex, NULL) != 0)
		return (1);
	while (i < prog->num_of_philos)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_philo(t_prog *prog, int index, int ac, char **av)
{
	t_philo *philo;
	
	philo = &prog->philo[index];
	
	philo->index = index;
	philo->num_of_philos = prog->num_of_philos;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->num_of_meals = ft_atoi(av[5]);
	else
		philo->num_of_meals = -1;
	philo->left_fork_mutex = &prog->forks[index];
	philo->right_fork_mutex = &prog->forks[(index + 1)
		% philo->num_of_philos];
}
