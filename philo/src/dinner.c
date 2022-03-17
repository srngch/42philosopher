/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:18:46 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/16 17:12:07 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_dinner(t_ph *ph)
{
	int i;

	i = 0;
	while (i < ph->num_of_philos)
	{
		pthread_join(ph->philos[i].thread, NULL);
		pthread_mutex_destroy(&ph->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&ph->printing);
}

int	start_dinner(t_ph *ph)
{
	int i;
	t_philo *philos;

	i = 0;
	philos = ph->philos;
	ph->start_time = get_time_ms();
	while (i < ph->num_of_philos)
	{
		if (pthread_create(&(philos[i].thread), NULL, philo_routine, &(philos[i])))
			return (FT_ERROR);
		philos[i].time_last_eat = get_time_ms();
		pthread_detach(philos[i].thread);
		i++;
	}
	return (FT_SUCCESS);
}
