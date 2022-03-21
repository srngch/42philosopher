/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:00:19 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/21 16:54:36 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time_ms(void)
{
	struct timeval	now;
	long long		time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time);
}

void	ph_print_log(t_ph *ph, int philo_id, char *str)
{
	long long	time;

	if (ph->someone_is_dead)
		return ;
	pthread_mutex_lock(&ph->printing);
	time = get_time_ms() - ph->start_time;
	printf("%lli %d %s\n", time, philo_id + 1, str);
	pthread_mutex_unlock(&ph->printing);
}

void	ph_usleep(t_ph *ph, int time)
{
	long long	start;
	long long	now;

	start = get_time_ms();
	while (!(ph->someone_is_dead))
	{
		now = get_time_ms();
		if (now - start >= time)
			break ;
		usleep(1000);
	}
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
