/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:36:29 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/15 03:00:12 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_ph	ph;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo [number of philosophers] [time to eat] \
			[time to sleep] [time to die] [number of time to eat]\n");
		return (EXIT_FAILURE);
	}
	if (ph_init(&ph, argv) == FT_ERROR)
	{
		printf("Error: init failed\n");
		return (EXIT_FAILURE);
	}
	if(start_dinner(&ph) == FT_ERROR)
		return (EXIT_FAILURE);
	death_observer(&ph);
	end_dinner(&ph);
	printf("[TEST] done\n");
	return (EXIT_SUCCESS);
}
