/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:01:42 by cmontaig          #+#    #+#             */
/*   Updated: 2025/10/13 12:54:18 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_prog *prog, int i)
{
	long	now;
	long	ttd;

	pthread_mutex_lock(&prog->eat_mutex);
	now = get_time();
	ttd = (long)prog->philo[i].time_to_die;
	if (now - prog->philo[i].last_meal >= ttd + 1L)
	{
		pthread_mutex_lock(&prog->print_mutex);
		printf("%ld %d died\n", now - prog->start_time,
			prog->philo[i].index + 1);
		pthread_mutex_unlock(&prog->print_mutex);
		pthread_mutex_lock(&prog->dead_mutex);
		prog->dead = true;
		pthread_mutex_unlock(&prog->dead_mutex);
		pthread_mutex_unlock(&prog->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&prog->eat_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_prog	*prog;
	int		full;

	prog = (t_prog *)arg;
	while (1)
	{
		if (check_philos(prog, &full))
			return (NULL);
		if (prog->philo[0].num_of_meals != -1
			&& full == prog->num_of_philos)
		{
			pthread_mutex_lock(&prog->dead_mutex);
			prog->dead = true;
			pthread_mutex_unlock(&prog->dead_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	check_philos(t_prog *prog, int *full)
{
	int	i;

	i = 0;
	*full = 0;
	while (i < prog->num_of_philos)
	{
		if (check_death(prog, i))
			return (1);
		pthread_mutex_lock(&prog->eat_mutex);
		if (prog->philo[i].num_of_meals != -1
			&& prog->philo[i].meals_eaten >= prog->philo[i].num_of_meals)
			(*full)++;
		pthread_mutex_unlock(&prog->eat_mutex);
		i++;
	}
	return (0);
}
