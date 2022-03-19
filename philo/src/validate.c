/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:18:03 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/20 01:37:36 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_ph(t_ph *ph)
{
	if (ph->num_of_philos < 0 || MAX_PHILOS < ph->num_of_philos)
		return (FT_FALSE);
	if (ph->time_to_die < 0)
		return (FT_FALSE);
	if (ph->time_to_eat < 0)
		return (FT_FALSE);
	if (ph->time_to_sleep < 0)
		return (FT_FALSE);
	if (ph->num_of_eat < 0)
		return (FT_FALSE);
	return (FT_TRUE);
}
