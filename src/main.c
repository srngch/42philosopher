/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:36:29 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/16 19:49:59 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_ph	ph;

	if (argc != 5 && argc != 6)
	{
		ph_print_error("Usage: ./philo [number of philosophers] [time to eat] \
			[time to sleep] [time to die] [number of time to eat]\n");
		return (EXIT_FAILURE);
	}
	if (ph_init(&ph, argv) == FT_ERROR)
	{
		ph_print_error("Error: init failed\n");
		return (EXIT_FAILURE);
	}
	if(start_dinner(&ph) == FT_ERROR)
		return (EXIT_FAILURE);
	death_observer(&ph);
	end_dinner(&ph);
	return (EXIT_SUCCESS);
}
