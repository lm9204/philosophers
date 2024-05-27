/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:31 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/26 20:28:30 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_th_data
{
	sem_t			*forks;
	sem_t			*c_sync;
	sem_t			*c_dead;
	sem_t			*c_print;
	sem_t			*c_eat_count;
	sem_t			*c_t_start;
	sem_t			*c_t_last_meal;
	struct timeval	*t_last_meal;
	struct timeval	t_start;
	long long		t_eat;
	long long		t_sleep;
	long long		t_die;
	int				is_dead;
	int				index;
	int				max_size;
	int				c_must_eat;
}	t_th_data;

typedef struct s_data
{
	sem_t			*forks;
	sem_t			*c_print;
	sem_t			*c_dead;
	sem_t			*c_sync;
	struct timeval	t_start;
	long long		t_eat;
	long long		t_sleep;
	long long		t_die;
	int				*pids;
	int				index;
	int				max_size;
	int				c_eat_count;
	int				c_must_eat;
}	t_data;

void		clear_threads(t_data *data);
int			ft_atoi_ovf(char *str);
int			check_stop(t_th_data *th);

void		ft_malloc_error(void);
void		ft_exit_error(char *str);

void		*routine(void *arg);
int			get_forks(t_th_data *thread);
int			drop_forks(t_th_data *thread);

long long	diff_tv(struct timeval *tv1, struct timeval *tv2);
long long	t_calc(struct timeval *tv1, struct timeval *tv2);
void		init_time(struct timeval *tv, struct timeval *val);
void		spend_time(long long time);
int			calc_last_time(t_th_data *thread);

void		p_eat(t_th_data *thread);
void		p_getfork(t_th_data *thread);
void		p_sleep(t_th_data *thread);
void		p_think(t_th_data *thread);
void		p_die(t_th_data *thread);

void		philo_create(t_data *data, int index);
#endif