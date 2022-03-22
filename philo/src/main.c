/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:36:29 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/22 16:54:37 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	end_dinner(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->num_of_philos)
	{
		pthread_join(ph->philos[i].thread, NULL);
		pthread_mutex_destroy(&ph->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&ph->printing);
}

static int	start_dinner(t_ph *ph)
{
	int			i;
	t_philo		*philos;

	i = 0;
	philos = ph->philos;
	ph->start_time = get_time_ms();
	while (i < ph->num_of_philos && !(ph->someone_is_dead))
	{
		if (pthread_create(&(philos[i].thread), NULL, \
		philo_routine, &(philos[i])))
			return (FT_ERROR);
		philos[i].time_last_eat = get_time_ms();
		pthread_detach(philos[i].thread);
		i++;
	}
	return (FT_SUCCESS);
}

static void	death_observer(t_ph *ph)
{
	int	i;

	while (!(ph->someone_is_dead))
	{
		i = 0;
		while (i < ph->num_of_philos)
		{
			if (get_time_ms() - ph->philos[i].time_last_eat > ph->time_to_die)
			{
				ph_print_log(ph, i, "died");
				ph->someone_is_dead = FT_TRUE;
				break ;
			}
			i++;
		}
		if (ph->someone_is_dead)
			break ;
		if (ph->num_of_eat != 0 && check_eating_done(ph))
			break ;
		ph_usleep(ph, 60);
	}
}

int	main(int argc, char **argv)
{
	t_ph	ph;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: Usage: ./philo number_of_philosophers time_to_eat \
time_to_sleep time_to_die [number_of_time_to_eat]\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ph_init(&ph, argv) == FT_ERROR)
	{
		ft_putstr_fd("Error: init failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (start_dinner(&ph) == FT_ERROR)
		return (EXIT_FAILURE);
	death_observer(&ph);
	end_dinner(&ph);
	return (EXIT_SUCCESS);
}
