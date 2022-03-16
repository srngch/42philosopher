/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:36:29 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/16 20:05:36 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_ph	ph;

	if (argc != 5 && argc != 6)
	{
		ph_print_error("Usage: ./philo number_of_philosophers time_to_eat \
time_to_sleep time_to_die [number_of_time_to_eat]\n");
		return (EXIT_FAILURE);
	}
	if (ph_init(&ph, argv) == FT_ERROR)
	{
		ph_print_error("Error: init failed\n");
		return (EXIT_FAILURE);
	}
	printf("%d %d %d %d %d\n", ph.num_of_philos, ph.time_to_die, ph.time_to_eat, ph.time_to_sleep, ph.num_of_eat);
	if(start_dinner(&ph) == FT_ERROR)
		return (EXIT_FAILURE);
	death_observer(&ph);
	end_dinner(&ph);
	return (EXIT_SUCCESS);
}
