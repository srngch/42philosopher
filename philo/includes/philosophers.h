/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:30:56 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/20 01:40:26 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>

# define	FT_SUCCESS 1
# define	FT_ERROR -1
# define	FT_TRUE 1
# define	FT_FALSE 0

# define	FT_USLEEP_TIME 10000
# define	MAX_PHILOS 200

# define PH_INT_MIN -2147483648
# define PH_INT_MAX 2147483647

struct	s_ph;

typedef struct s_philo
{
	struct s_ph	*ph;
	int			id;
	int			eat_count;
	int			id_left_fork;
	int			id_right_fork;
	long long	time_last_eat;
	pthread_t	thread;
}							t_philo;

typedef struct s_ph
{
	int							num_of_philos;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							num_of_eat;
	t_philo						philos[MAX_PHILOS];
	pthread_mutex_t		[MAX_PHILOS];
	pthread_mutex_t				printing;
	long long					start_time;
	int							someone_is_dead;
}								t_ph;

/*
** init.c
*/
int				ph_init(t_ph *ph, char **argv);

/*
** philo.c
*/
void			*philo_routine(void *philo_arg);

/*
** util.c
*/
long long		get_time_ms(void);
void			ph_print_log(t_ph *ph, int philo_id, char *str);
void			ph_usleep(t_ph *ph, int time);

/*
** util2.c
*/
int				ft_atoi(const char *str);
long			ft_atol(const char *str);

/*
** validate.c
*/
int				validate_ph(t_ph *ph);

/*
** check.c
*/
int				check_integer(char *str);
int				check_range(char *str);
int				check_eating_done(t_ph *ph);

#endif
