/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:53:17 by cmontaig          #+#    #+#             */
/*   Updated: 2025/10/13 14:29:09 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac < 5 || ac > 6)
	{
		printf("Too many or too few arguments\n");
		return (1);
	}
	if (check_input(av) == 1)
	{
		printf("Arguments invalid\n");
		return (1);
	}
	if (init_struct(&prog, ac, av))
	{
		printf("Arguments invalid\n");
		return (1);
	}
	if (create_threads(&prog))
	{
		printf("Thread creation failed\n");
		return (1);
	}
	free_all(&prog);
	return (0);
}

int	create_threads(t_prog *prog)
{
	int	i;

	prog->start_time = get_time();
	i = -1;
	while (++i < prog->num_of_philos)
		prog->philo[i].last_meal = prog->start_time;
	i = -1;
	while (++i < prog->num_of_philos)
	{
		if (pthread_create(&prog->philo[i].thread, NULL, routine_philo,
				&prog->philo[i]) != 0)
			return (1);
		usleep(100);
	}
	if (pthread_create(&prog->monitor_thread, NULL, monitor, prog) != 0)
		return (1);
	i = -1;
	while (++i < prog->num_of_philos)
		if (pthread_join(prog->philo[i].thread, NULL) != 0)
			return (1);
	if (pthread_join(prog->monitor_thread, NULL) != 0)
		return (1);
	return (0);
}

void	print_states(t_philo *philo, const char *state)
{
	long	time;

	pthread_mutex_lock(&philo->prog->print_mutex);
	if (!is_dead(philo->prog))
	{
		time = get_time() - philo->prog->start_time;
		printf("%ld %d %s\n", time, philo->index + 1, state);
	}
	pthread_mutex_unlock(&philo->prog->print_mutex);
}

void	free_all(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prog->dead_mutex);
	pthread_mutex_destroy(&prog->eat_mutex);
	pthread_mutex_destroy(&prog->print_mutex);
	free(prog->forks);
	free(prog->philo);
}
