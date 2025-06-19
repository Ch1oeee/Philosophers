/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:53:17 by cmontaig          #+#    #+#             */
/*   Updated: 2025/06/19 12:49:59 by cmontaig         ###   ########.fr       */
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
		printf("Arguments are not numbers\n");
		return (1);
	}
	if (init_struct(&prog, ac, av))
	{
		printf("Numbers should be above 0\n");
		return (1);
	}
	if (create_threads(&prog))
	{
		printf("Thread creation failed\n");
		return (1);
	}
	return (0);
}

int	create_threads(t_prog *prog)
{
	int	i;

	i = 0;
	prog->start_time = get_time();
	while(i < prog->num_of_philos)
	{
		if(pthread_create(prog->philo[i].thread, NULL, routine_philo, &prog->philo[i]) != 0)
		{
			printf("Failed to create thread for philosopher %d\n", i);
			return (1);
		}
		i++;
	}
	if (pthread_create(&prog->monitor_thread, NULL, monitor, prog) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (1);
	}
	i = 0;
	while (i < prog->num_of_philos)
	{
		if (pthread_join(prog->philo[i].thread, NULL) != 0)
		{
			printf("Failed to join thread for philosopher %d\n", i);
			return (1);
		}
		i++;
	}
	if (pthread_join(prog->monitor_thread, NULL) != 0)
	{
		printf("Failed to join monitor thread\n");
		return (1);
	}
	return (0);
}
int	check_death(t_prog *prog, int i)
{
	pthread_mutex_lock(&prog->eat_mutex);
	if ((get_time() - prog->philo[i].last_meal) > prog->philo[i].time_to_die)
	{
		pthread_mutex_lock(&prog->print_mutex);
		printf("%ld %d died\n", get_time() - prog->start_time,
			prog->philo[i].index + 1);
		pthread_mutex_unlock(&prog->print_mutex);
		prog->dead = true;
		pthread_mutex_unlock(&prog->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&prog->eat_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_prog	*prog;
	int		i;
	int		full;

	prog = (t_prog *)arg;
	while (1)
	{
		i = 0;
		full = 0;
		while (i < prog->num_of_philos)
		{
			if (check_death(prog, i))
				return (NULL);
			if (prog->philo[i].num_of_meals != -1 &&
				prog->philo[i].meals_eaten >= prog->philo[i].num_of_meals)
				full++;
			i++;
		}
		if (prog->philo[0].num_of_meals != -1 &&
			full == prog->num_of_philos)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}


void	*routine_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(philo->prog->dead)
	{
		
	}
}

void	print_states(t_philo *philo, char *state)
{
	long	time;
	if(philo->prog->dead)
		return ;
	pthread_mutex_lock(&philo->prog->print_mutex);
	time = get_time() - philo->prog->start_time;
	printf("%ld %d %s\n", time, philo->index + 1, state);
	pthread_mutex_unlock(&philo->prog->print_mutex);
}

////// 		TO DO LIST		 /////

//un thread to monitor if anybody died like a loser
// creer les thread (un par philo i think)


// 5 800 200 200 7

// 5 — The number of philosophers
// 800 — The time a philosopher will die if he doesn’t eat
// 200 — The time it takes a philosopher to eat
// 200 — The time it takes a philosopher to sleep
// 7 — Number of times all the philosophers need to eat before terminating the program *
// ** optional argument

//mutex pour les printfindex