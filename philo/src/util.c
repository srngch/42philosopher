/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:00:19 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/17 15:04:41 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

long long	get_time_ms(void)
{
	struct timeval now;
	long long time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time);
}

void	ph_print_log(t_ph *ph, int philo_id, char *str)
{
	long long time;

	pthread_mutex_lock(&ph->printing);
	time = get_time_ms() - ph->start_time;
	printf("%lli %d %s\n", time, philo_id + 1, str);
	pthread_mutex_unlock(&ph->printing);
}

void	ph_print_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
}

void	ph_usleep(t_ph *ph, int time)
{
	long long start;
	long long now;

	start = get_time_ms();
	while (!(ph->someone_is_dead))
	{
		now = get_time_ms();
		if (now - start >= time)
			break ;
		usleep(1000);
	}
}
