/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:02:31 by cmontaig          #+#    #+#             */
/*   Updated: 2025/10/13 13:03:32 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_fork(t_philo *philo)
{
	if (is_dead(philo->prog))
		return (1);
	if (philo->index % 2 == 0)
		return (fork_pair(philo));
	else
		return (fork_odd(philo));
}

int	fork_pair(t_philo *philo)
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
