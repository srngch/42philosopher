/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:45:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/17 14:43:14 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutex(t_ph *ph)
{
	int i;

	i = 0;
	while (i < ph->num_of_philos)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL) != 0)
			return (FT_ERROR);
		i++;
	}
	if (pthread_mutex_init(&ph->printing, NULL) != 0)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

static int	init_philosophers(t_ph *ph)
{
	int i;

	i = 0;
	while (i < ph->num_of_philos)
	{
		ph->philos[i].ph = ph;
		ph->philos[i].id = i;
		ph->philos[i].eat_count = 0;
		ph->philos[i].id_left_fork = i;
		ph->philos[i].id_right_fork = (i + 1) % ph->num_of_philos;
		ph->philos[i].time_last_eat = 0;
		i++;
	}
	return (FT_SUCCESS);
}

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

int	validate_args(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (!check_integer(argv[i]) || !check_range(argv[i]))
			return (FT_ERROR);
		i++;
	}
	return (FT_SUCCESS);
}

static int	init_args(t_ph *ph, char **argv)
{

	ph->num_of_philos = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	ph->num_of_eat = 0;
	ph->someone_is_dead = FT_FALSE;
	if (argv[5] != NULL)
		ph->num_of_eat = ft_atoi(argv[5]);
	if (!validate_ph(ph))
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ph_init(t_ph *ph, char **argv)
{
	if (validate_args(argv) == FT_ERROR)
		return (FT_ERROR);
	if (init_args(ph, argv) == FT_ERROR)
		return (FT_ERROR);
	if (init_philosophers(ph) == FT_ERROR)
		return (FT_ERROR);
	if (init_mutex(ph) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
