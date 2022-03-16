/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:30:56 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/16 20:18:07 by sarchoi          ###   ########seoul.kr  */
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

struct s_ph;

typedef struct s_philo
{
	struct s_ph		*ph;
	int						id;
	int						eat_count;
	int						id_left_fork;
	int						id_right_fork;
	long long			time_last_eat;
	pthread_t			thread;
}								t_philo;

typedef struct s_ph
{
	int							num_of_philos;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							num_of_eat;
	t_philo					philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	printing;
	long long				start_time;
	int							someone_is_dead;
}								t_ph;

int	ft_atoi(const char *str);
void  ft_putstr_fd(char *s, int fd);
int	ft_isdigit(int c);

/*
** init.c
*/
int	ph_init(t_ph *ph, char **argv);

/*
** dinner.c
*/
int	start_dinner(t_ph *ph);
void	end_dinner(t_ph *ph);

/*
** action.c
*/
void	*philo_routine(void *philo_arg);

/*
** util.c
*/
long long	get_time_ms(void);
void	ph_print_log(t_ph *ph, int philo_id, char *str);
void	ph_print_error(char *str);
void	ph_usleep(t_ph *ph, int time);

/*
** validate.c
*/
int	validate_ph(t_ph *ph);

/*
** check.c
*/
int	complete_eating(t_ph *ph);
void	death_observer(t_ph *ph);

#endif
