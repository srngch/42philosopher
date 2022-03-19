/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 03:06:02 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/19 22:31:18 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_integer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			i++;
		if (!ft_isdigit(str[i]))
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

int	check_range(char *str)
{
	if (ft_atol(str) < PH_INT_MIN || ft_atol(str) > PH_INT_MAX)
		return (FT_FALSE);
	return (FT_TRUE);
}

int	check_eating_done(t_ph *ph)
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
