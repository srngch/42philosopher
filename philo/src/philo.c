/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:11:55 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/21 19:09:13 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eating(t_ph *ph, t_philo *philo)
{
	if (ph->someone_is_dead)
		return ;
	if (philo->time_last_eat + ph->time_to_eat < \
	philo->time_last_eat + ph->time_to_die)
		usleep(ph->time_to_eat);
	pthread_mutex_lock(&ph->forks[philo->id_left_fork]);
	ph_print_log(ph, philo->id, "has taken a fork");
	if (ph->someone_is_dead)
		return ;
	pthread_mutex_lock(&ph->forks[philo->id_right_fork]);
	ph_print_log(ph, philo->id, "has taken a fork");
	ph_print_log(ph, philo->id, "is eating");
	philo->time_last_eat = get_time_ms();
	philo->eat_count++;
	ph_usleep(ph, ph->time_to_eat);
	pthread_mutex_unlock(&ph->forks[philo->id_left_fork]);
	pthread_mutex_unlock(&ph->forks[philo->id_right_fork]);
}

static void	philo_sleeping(t_ph *ph, t_philo *philo)
{
	if (ph->someone_is_dead)
		return ;
	ph_print_log(ph, philo->id, "is sleeping");
	ph_usleep(ph, philo->ph->time_to_sleep);
}

static void	philo_thinking(t_ph *ph, t_philo *philo)
{
	if (ph->someone_is_dead)
		return ;
	ph_print_log(ph, philo->id, "is thinking");
}

void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	if (philo->id % 2)
		usleep(philo->ph->time_to_eat);
	while (!((philo->ph)->someone_is_dead))
	{
		philo_eating(philo->ph, philo);
		if (philo->ph->someone_is_dead
			|| (philo->ph->num_of_eat != 0 && check_eating_done(philo->ph)))
			break ;
		philo_sleeping(philo->ph, philo);
		philo_thinking(philo->ph, philo);
	}
	return ((void *)0);
}
