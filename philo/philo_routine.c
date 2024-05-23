/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:16:44 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/23 14:08:04 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_fork_usable(t_th_data *th, pthread_mutex_t *dir, \
int *dir_val)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(dir);
	if (*dir_val == 0)
	{
		*dir_val = 1;
		p_getfork(th);
		ret = 0;
	}
	pthread_mutex_unlock(dir);
	return (ret);
}

static	int	choose_fork(t_th_data *thread)
{
	while (check_fork_usable(thread, thread->m_left, thread->left))
	{
		if (!calc_last_time(thread) || !check_stop(thread))
			return (0);
		usleep(100);
	}
	if (!calc_last_time(thread) || !check_stop(thread))
		return (0);
	while (check_fork_usable(thread, thread->m_right, thread->right))
	{
		if (!calc_last_time(thread) || !check_stop(thread))
			return (0);
		usleep(100);
	}
	if (!calc_last_time(thread) || !check_stop(thread))
		return (0);
	return (1);
}

int	get_forks(t_th_data *thread)
{
	struct timeval	time;

	if (!choose_fork(thread))
		return (0);
	if (thread->c_must_eat > 0)
	{
		pthread_mutex_lock(&thread->c_eat);
		thread->c_must_eat--;
		pthread_mutex_unlock(&thread->c_eat);
	}
	p_eat(thread);
	gettimeofday(&time, NULL);
	thread->t_last_meal.tv_sec = time.tv_sec;
	thread->t_last_meal.tv_usec = time.tv_usec;
	spend_time(thread->t_eat);
	drop_forks(thread);
	return (1);
}

int	drop_forks(t_th_data *thread)
{
	pthread_mutex_lock(thread->m_left);
	*thread->left = 0;
	pthread_mutex_unlock(thread->m_left);
	pthread_mutex_lock(thread->m_right);
	*thread->right = 0;
	pthread_mutex_unlock(thread->m_right);
	return (1);
}

void	*routine(void *arg)
{
	t_th_data	*ptr;
	int			c_loop;

	ptr = (t_th_data *)arg;
	p_think(ptr);
	if (ptr->index % 2 == 0)
		spend_time(ptr->t_eat);
	if (ptr->max_size % 2 == 1 && ptr->index == 0)
		spend_time(ptr->t_eat);
	c_loop = 1;
	if (ptr->c_must_eat > 0)
		c_loop = 0;
	while (c_loop || ptr->c_must_eat > 0)
	{
		if (!calc_last_time(ptr) || !get_forks(ptr) || !check_stop(ptr))
			break ;
		p_sleep(ptr);
		spend_time(ptr->t_sleep);
		if (!calc_last_time(ptr) || !check_stop(ptr))
			break ;
		p_think(ptr);
	}
	return (NULL);
}
