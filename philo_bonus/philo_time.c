/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:14:27 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/26 21:56:15 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spend_time(long long time)
{
	struct timeval	start_tv;
	struct timeval	cur_tv;

	gettimeofday(&start_tv, NULL);
	gettimeofday(&cur_tv, NULL);
	while (time * 1000 >= diff_tv(&cur_tv, &start_tv))
	{
		usleep(100);
		gettimeofday(&cur_tv, NULL);
	}
}

long long	diff_tv(struct timeval *tv1, struct timeval *tv2)
{
	long long	sec_diff;
	long long	usec_diff;

	sec_diff = tv1->tv_sec - tv2->tv_sec;
	usec_diff = tv1->tv_usec - tv2->tv_usec;
	return (sec_diff * 1000000 + usec_diff);
}

long long	t_calc(struct timeval *tv1, struct timeval *tv2)
{
	return (diff_tv(tv1, tv2) / 1000);
}

int	calc_last_time(t_th_data *thread)
{
	struct timeval	time;
	int				ret;

	ret = 1;
	gettimeofday(&time, NULL);
	sem_wait(thread->c_t_last_meal);
	if ((thread->t_last_meal == NULL \
	&& diff_tv(&time, &thread->t_start) > thread->t_die * 1000) \
	|| (thread->t_last_meal != NULL \
	&& diff_tv(&time, thread->t_last_meal) > thread->t_die * 1000))
	{
		sem_wait(thread->c_dead);
		thread->is_dead = 1;
		p_die(thread);
		sem_post(thread->c_dead);
		ret = 0;
	}
	sem_post(thread->c_t_last_meal);
	// if (thread->max_size == 1)
	// {
	// 	spend_time(thread->t_die);
	// 	sem_wait(thread->c_dead);
	// 	thread->is_dead = 1;
	// 	p_die(thread);
	// 	sem_post(thread->c_dead);
	// 	ret = 0;
	// }
	return (ret);
}

void	init_time(struct timeval *tv, struct timeval *val)
{
	if (val == NULL)
	{
		tv->tv_sec = 0;
		tv->tv_usec = 0;
	}
	else
	{
		tv->tv_sec = val->tv_sec;
		tv->tv_usec = val->tv_usec;
	}
}
