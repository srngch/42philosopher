/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:18:46 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/16 03:09:22 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eating(t_ph *ph, t_philo *philo)
{
	if (ph->is_dead)
		return ;
	if (philo->time_last_eat + ph->time_to_eat < \
	philo->time_last_eat + ph->time_to_die)
		ph_usleep(ph, 10);
	pthread_mutex_lock(&ph->forks[philo->id_left_fork]);
	ph_print_log(ph, philo->id, "has taken a L fork");
	pthread_mutex_lock(&ph->forks[philo->id_right_fork]);
	ph_print_log(ph, philo->id, "has taken a R fork");
	ph_print_log(ph, philo->id, "is eating");
	philo->time_last_eat = get_time_ms();
	philo->eat_count++;
	ph_usleep(ph, ph->time_to_eat);
	pthread_mutex_unlock(&ph->forks[philo->id_left_fork]);
	pthread_mutex_unlock(&ph->forks[philo->id_right_fork]);
}

void	philo_sleeping(t_ph *ph, t_philo *philo)
{
	if (ph->is_dead)
		return ;
	ph_print_log(ph, philo->id, "is sleeping");
	ph_usleep(ph, philo->ph->time_to_sleep);
}

void	philo_thinking(t_ph *ph, t_philo *philo)
{
	if (ph->is_dead)
		return ;
	ph_print_log(ph, philo->id, "is thinking");
}

void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	if (philo->id % 2)
		usleep(5000);
	while (!((philo->ph)->is_dead))
	{
		philo_eating(philo->ph, philo);
		if (philo->ph->is_dead ||
		(philo->ph->num_of_eat != 0 && complete_eating(philo->ph)))
			break ;
		philo_sleeping(philo->ph, philo);
		philo_thinking(philo->ph, philo);
		// ph_print_log(philo->ph, philo->id, "is sleeping");
		// ph_usleep(philo->ph, philo->ph->time_to_sleep);
		// ph_print_log(philo->ph, philo->id, "is thinking");
	}
	return ((void *)0);
}

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
	ph->is_dead = FT_FALSE;
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
