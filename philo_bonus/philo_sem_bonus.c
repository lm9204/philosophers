/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:25:51 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/28 12:04:19 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_data *data)
{
	sem_unlink("s_fork");
	sem_unlink("s_dead");
	sem_unlink("s_print");
	sem_unlink("s_sync");
	sem_unlink("c_t_last_meal");
	sem_unlink("s_done");
	data->forks = sem_open("s_fork", O_CREAT, S_IRWXU, data->max_size);
	data->s_dead = sem_open("s_dead", O_CREAT, S_IRWXU, 1);
	data->s_print = sem_open("s_print", O_CREAT, S_IRWXU, 1);
	data->s_sync = sem_open("s_sync", O_CREAT, S_IRWXU, 0);
	data->s_t_last = sem_open("c_t_last_meal", O_CREAT, S_IRWXU, 1);
	data->s_done = sem_open("s_done", O_CREAT, S_IRWXU, data->max_size);
	data->pids = malloc(sizeof(int) * data->max_size);
}

void	wait_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_size)
	{
		sem_wait(data->s_done);
		i++;
	}
}

void	clear_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_size)
		kill(data->pids[i++], SIGKILL);
	sem_close(data->forks);
	sem_close(data->s_t_last);
	sem_close(data->s_done);
	sem_close(data->s_dead);
	sem_close(data->s_print);
	sem_close(data->s_sync);
}

void	start_sync(t_data *data)
{
	struct timeval	time;
	int				i;

	i = 0;
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec > data->t_start.tv_sec \
		|| (time.tv_sec == data->t_start.tv_sec \
		&& time.tv_usec > data->t_start.tv_usec))
			break ;
		usleep(100);
	}
	while (i < data->max_size)
	{
		sem_post(data->s_sync);
		i++;
	}
}
