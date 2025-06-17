/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:53:17 by cmontaig          #+#    #+#             */
/*   Updated: 2025/06/17 16:21:50 by cmontaig         ###   ########.fr       */
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
	// create_threads(&prog);
	return (0);
}

int	create_threads(t_prog *prog)
{
	
}

// int	routine(t_prog *prog)
// {
// 	prog->start_time = get_time();
// }

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