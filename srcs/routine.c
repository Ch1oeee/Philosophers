/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:47:45 by cmontaig          #+#    #+#             */
/*   Updated: 2025/06/23 17:15:30 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_of_philos == 1)
	{
		print_states(philo, "has taken a fork");
		safe_usleep(philo->time_to_die, philo->prog);
		return (NULL);
	}
	while (!is_dead(philo->prog))
	{
		if (take_fork(philo))
			break ;
		eating(philo);
		release_forks(philo);
		if (philo->num_of_meals != -1
			&& philo->meals_eaten >= philo->num_of_meals)
			break ;
		print_states(philo, "is sleeping");
		safe_usleep(philo->time_to_sleep, philo->prog);
		if (is_dead(philo->prog))
			break ;
		print_states(philo, "is thinking");
		usleep(100);
	}
	release_forks(philo);
	return (NULL);
}

void	release_forks(t_philo *philo)
{
	if (philo->has_left)
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		philo->has_left = 0;
	}
	if (philo->has_right)
	{
		pthread_mutex_unlock(philo->right_fork_mutex);
		philo->has_right = 0;
	}
}


// void	eating(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->prog->eat_mutex);
// 	philo->last_meal = get_time();
// 	print_states(philo, "is eating");
// 	pthread_mutex_unlock(&philo->prog->eat_mutex);
// 	safe_usleep(philo->time_to_eat, philo->prog);
// 	pthread_mutex_lock(&philo->prog->eat_mutex);
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(&philo->prog->eat_mutex);
// 	pthread_mutex_unlock(philo->left_fork_mutex);
// 	pthread_mutex_unlock(philo->right_fork_mutex);
// }

void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->eat_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->prog->eat_mutex);

	print_states(philo, "is eating");
	safe_usleep(philo->time_to_eat, philo->prog);

	pthread_mutex_lock(&philo->prog->eat_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->prog->eat_mutex);
}


// int	take_fork(t_philo *philo)
// {
// 	if (is_dead(philo->prog))
// 		return (1);
// 	if (philo->index % 2 == 0)
// 	{
// 		if (fork_pair(philo))
// 			return (1);
// 	}
// 	else
// 	{
// 		if (fork_odd(philo))
// 			return (1);
// 	}
// 	return (0);
// }

// int fork_pair(t_philo *philo)
// {
//     if (is_dead(philo->prog))
//         return (1);
//     pthread_mutex_lock(philo->right_fork_mutex);
//     print_states(philo, "has taken a fork");
//     if (is_dead(philo->prog)) {
//         pthread_mutex_unlock(philo->right_fork_mutex);
//         return (1);
//     }
//     pthread_mutex_lock(philo->left_fork_mutex);
//     print_states(philo, "has taken a fork");
//     if (is_dead(philo->prog)) {
//         pthread_mutex_unlock(philo->left_fork_mutex);
//         pthread_mutex_unlock(philo->right_fork_mutex);
//         return (1);
//     }
//     return (0);
// }


// int	fork_odd(t_philo *philo)
// {
// 	if (is_dead(philo->prog))
// 		return (1);
// 	pthread_mutex_lock(philo->left_fork_mutex);
// 	print_states(philo, "has taken a fork");
// 	if (is_dead(philo->prog))
// 	{
// 		pthread_mutex_unlock(philo->left_fork_mutex);
// 		return (1);
// 	}
// 	if (is_dead(philo->prog)) {
// 		pthread_mutex_unlock(philo->left_fork_mutex);
// 		return (1);
//     }
// 	pthread_mutex_lock(philo->right_fork_mutex);
// 	print_states(philo, "has taken a fork");
// 	if (is_dead(philo->prog))
// 	{
// 		pthread_mutex_unlock(philo->right_fork_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

int	take_fork(t_philo *philo)
{
	if (is_dead(philo->prog))
		return (1);
	if (philo->index % 2 == 0)
		return (fork_pair(philo));
	else
		return (fork_odd(philo));
}

int fork_pair(t_philo *philo)
{
	if (is_dead(philo->prog))
		return (1);
	pthread_mutex_lock(philo->right_fork_mutex);
	philo->has_right = 1;
	print_states(philo, "has taken a fork");
	if (is_dead(philo->prog))
		return (1);

	pthread_mutex_lock(philo->left_fork_mutex);
	philo->has_left = 1;
	print_states(philo, "has taken a fork");
	if (is_dead(philo->prog))
		return (1);

	return (0);
}

int	fork_odd(t_philo *philo)
{
	if (is_dead(philo->prog))
		return (1);
	pthread_mutex_lock(philo->left_fork_mutex);
	philo->has_left = 1;
	print_states(philo, "has taken a fork");
	if (is_dead(philo->prog))
		return (1);

	pthread_mutex_lock(philo->right_fork_mutex);
	philo->has_right = 1;
	print_states(philo, "has taken a fork");
	if (is_dead(philo->prog))
		return (1);

	return (0);
}

