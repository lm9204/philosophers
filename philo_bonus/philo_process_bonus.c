/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:27:49 by yeondcho          #+#    #+#             */
/*   Updated: 2024/06/18 14:58:20 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_th_data	*init_thread(t_data *data, int index)
{
	t_th_data	*ptr;

	ptr = malloc(sizeof(t_th_data));
	if (ptr == NULL)
		return (NULL);
	ptr->index = index;
	ptr->forks = data->forks;
	ptr->s_dead = data->s_dead;
	ptr->s_print = data->s_print;
	ptr->s_sync = data->s_sync;
	ptr->s_t_last = data->s_t_last;
	ptr->t_start = data->t_start;
	ptr->t_die = data->t_die;
	ptr->t_eat = data->t_eat;
	ptr->t_sleep = data->t_sleep;
	ptr->is_dead = 0;
	ptr->max_size = data->max_size;
	ptr->eat_count = data->eat_count;
	ptr->t_last_meal.tv_sec = 0;
	ptr->t_last_meal.tv_usec = 0;
	return (ptr);
}

static int	still_reachable(t_th_data *thread, t_data *data)
{
	sem_wait(thread->s_dead);
	if (thread->is_dead == 1)
	{
		sem_post(thread->s_dead);
		return (0);
	}
	sem_post(thread->s_dead);
	if (data->f_eatcount == 0)
		return (1);
	sem_wait(thread->s_count);
	if (thread->eat_count <= 0)
	{
		data->f_eatcount = 0;
		sem_post(data->s_done);
	}
	sem_post(thread->s_count);
	return (1);
}

static int	time_monitoring(t_th_data *thread, t_data *data)
{
	struct timeval	time;
	int				i;

	i = -1;
	sem_wait(thread->s_t_last);
	gettimeofday(&time, NULL);
	if ((thread->t_last_meal.tv_sec == 0 \
	&& diff_tv(&time, &thread->t_start) > thread->t_die * 1000) \
	|| (thread->t_last_meal.tv_sec != 0 \
	&& diff_tv(&time, &thread->t_last_meal) > thread->t_die * 1000))
	{
		sem_post(thread->s_t_last);
		sem_wait(thread->s_dead);
		thread->is_dead = 1;
		sem_post(thread->s_dead);
		sem_wait(thread->s_print);
		printf("%lld %d died\n", \
		t_calc(&time, &thread->t_start), thread->index + 1);
		while (++i < thread->max_size)
			sem_post(data->s_done);
		return (0);
	}
	return (1);
}

void	philo_create(t_data *data, int index)
{
	t_th_data		*th_data;
	pthread_t		thread;

	th_data = init_thread(data, index);
	if (!th_data)
		ft_malloc_error();
	if (pthread_create(&thread, NULL, routine, (void *)th_data) != 0)
		exit(1);
	while (still_reachable(th_data, data))
	{
		if (!time_monitoring(th_data, data))
			break ;
		sem_post(th_data->s_t_last);
		usleep(100);
	}
	pthread_join(thread, NULL);
	if (!th_data->is_dead)
		sem_post(data->s_done);
	exit(0);
}
