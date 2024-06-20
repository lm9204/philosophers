/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:31 by yeondcho          #+#    #+#             */
/*   Updated: 2024/06/17 21:46:26 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_th_data
{
	pthread_mutex_t	*m_left;
	pthread_mutex_t	*m_right;
	pthread_mutex_t	*m_dead;
	pthread_mutex_t	*m_print;
	pthread_mutex_t	m_eat;
	struct timeval	t_start;
	struct timeval	t_last_meal;
	long long		t_eat;
	long long		t_sleep;
	long long		t_die;
	int				*print;
	int				*is_dead;
	int				*left;
	int				*right;
	int				c_must_eat;
	int				index;
	int				max_size;
}	t_th_data;

typedef struct s_data
{
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_print;
	struct timeval	t_start;
	pthread_t		*threads;
	t_th_data		**datas;
	int				*forks;
	int				print;
	int				is_dead;
	int				f_eatcount;
	int				max_size;
}	t_data;

void		clear_threads(t_data *data);
int			check_printable(t_th_data *thread);
int			ft_atoi_ovf(char *str);
int			check_stop(t_th_data *th);

void		ft_malloc_error(void);
void		ft_exit_error(char *str);

void		*routine(void *arg);
int			get_forks(t_th_data *thread);
int			drop_forks(t_th_data *thread);

int			calc_last_time(t_th_data *thread);
void		spend_time(t_th_data *thread, long long time);
long long	diff_tv(struct timeval *tv1, struct timeval *tv2);
long long	t_calc(struct timeval *tv1, struct timeval *tv2);
void		init_time(struct timeval *tv, struct timeval *val);

void		p_eat(t_th_data *thread);
void		p_getfork(t_th_data *thread);
void		p_sleep(t_th_data *thread);
void		p_think(t_th_data *thread);
void		p_die(t_th_data *thread);

void		init_mutex(t_data *data, char **argv, int argc);
#endif