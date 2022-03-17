/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 03:06:02 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/16 19:55:35 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	complete_eating(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->num_of_philos)
	{
		if (ph->philos[i].eat_count < ph->num_of_eat)
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

void	death_observer(t_ph *ph)
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
		if (ph->num_of_eat != 0 && complete_eating(ph))
			break ;
		ph_usleep(ph, 1000);
	}
}
