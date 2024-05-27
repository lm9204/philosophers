/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:27:49 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/27 10:53:14 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_th_data	*init_thread(t_data *data, int index)
{
	t_th_data	*ptr;

	ptr = malloc(sizeof(t_th_data));
	if (ptr == NULL)
		return (NULL);
	ptr->index = index;
	ptr->forks = data->forks;
	ptr->c_dead = data->c_dead;
	ptr->c_print = data->c_print;
	ptr->c_sync = data->c_sync;
	sem_unlink("c_eat_count");
	sem_unlink("c_t_last_meal");
	ptr->c_eat_count = sem_open("c_eat_count", O_CREAT, S_IRWXU, 1);
	ptr->c_t_last_meal = sem_open("c_t_last_meal", O_CREAT, S_IRWXU, 1);
	if (!ptr->c_eat_count || !ptr->c_t_last_meal)
		return (NULL);
	ptr->t_start = data->t_start;
	ptr->t_die = data->t_die;
	ptr->t_eat = data->t_eat;
	ptr->t_sleep = data->t_sleep;
	ptr->c_must_eat = 0;
	sem_wait(ptr->c_dead);
	ptr->is_dead = 0;
	sem_post(ptr->c_dead);
	ptr->max_size = data->max_size;
	ptr->c_must_eat = data->c_must_eat;
	sem_wait(ptr->c_t_last_meal);
	ptr->t_last_meal = NULL;
	sem_post(ptr->c_t_last_meal);
	return (ptr);
}

static int	still_reachable(t_th_data *thread, int f_eat_arg)
{
	if (f_eat_arg == 0)
		return (1);
	sem_wait(thread->c_dead);
	if (thread->is_dead == 1)
	{
		sem_post(thread->c_dead);
		return (0);
	}
	sem_post(thread->c_dead);
	return (0);
}

void	philo_create(t_data *data, int index)
{
	t_th_data		*th_data;
	pthread_t		thread;

	th_data = init_thread(data, index);
	if (!th_data)
		ft_malloc_error();
	sem_wait(data->c_sync);
	if (pthread_create(&thread, NULL, routine, (void *)th_data) != 0)
		exit(1);
	while (still_reachable(th_data, data->c_eat_count))
	{
		if (!calc_last_time(th_data))
			break ;
		usleep(100);
	}
	pthread_join(thread, NULL);
	sem_close(th_data->c_eat_count);
	exit(0);
}
