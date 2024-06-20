/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:14:27 by yeondcho          #+#    #+#             */
/*   Updated: 2024/06/17 21:52:31 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spend_time(t_th_data *thread, long long time)
{
	struct timeval	start_tv;
	struct timeval	cur_tv;

	gettimeofday(&start_tv, NULL);
	if (thread->t_last_meal.tv_sec == 0 && diff_tv(&start_tv, &thread->t_start) \
	+ time * 1000 > thread->t_die * 1000)
	{
		time = thread->t_die \
		- diff_tv(&start_tv, &thread->t_start) / 1000;
	}
	if (thread->t_last_meal.tv_sec != 0 && \
	diff_tv(&start_tv, &thread->t_last_meal) + time * 1000 \
	> thread->t_die * 1000)
	{
		time = thread->t_die \
		- diff_tv(&start_tv, &thread->t_last_meal) / 1000;
	}
	usleep(time * 1000 * 0.7);
	gettimeofday(&cur_tv, NULL);
	while (time * 1000 >= diff_tv(&cur_tv, &start_tv))
	{
		usleep(1000);
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

	gettimeofday(&time, NULL);
	if ((thread->t_last_meal.tv_sec == 0 \
	&& diff_tv(&time, &thread->t_start) > thread->t_die * 1000) \
	|| (thread->t_last_meal.tv_sec != 0 \
	&& diff_tv(&time, &thread->t_last_meal) > thread->t_die * 1000))
	{
		pthread_mutex_lock(thread->m_dead);
		*thread->is_dead = 1;
		pthread_mutex_unlock(thread->m_dead);
		p_die(thread);
		return (0);
	}
	return (1);
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
