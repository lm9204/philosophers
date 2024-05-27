/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:37 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/26 21:07:25 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_start_time(struct timeval *t_start, int milliseconds)
{
	int	microseconds;

	microseconds = milliseconds * 1000;
	t_start->tv_usec += microseconds;

	while (t_start->tv_usec >= 1000000)
	{
		t_start->tv_sec += 1;
		t_start->tv_usec -= 1000000;
	}
}

static t_data	*init_struct(char **argv, int argc)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->max_size = ft_atoi_ovf(argv[1]);
	sem_unlink("s_fork");
	sem_unlink("s_dead");
	sem_unlink("s_print");
	sem_unlink("s_sync");
	data->forks = sem_open("s_fork", O_CREAT, S_IRWXU, data->max_size);
	data->c_dead = sem_open("s_dead", O_CREAT, S_IRWXU, 1);
	data->c_print = sem_open("s_print", O_CREAT, S_IRWXU, 1);
	data->c_sync = sem_open("s_sync", O_CREAT, S_IRWXU, 0);
	data->pids = malloc(sizeof(int) * data->max_size);
	if (!data->forks || !data->c_dead || !data->c_print || !data->pids)
		return (NULL);
	gettimeofday(&data->t_start, NULL);
	init_start_time(&data->t_start, 200);
	data->t_die = ft_atoi_ovf(argv[2]);
	data->t_eat = ft_atoi_ovf(argv[3]);
	data->t_sleep = ft_atoi_ovf(argv[4]);
	data->c_must_eat = 0;
	data->c_eat_count = 0;
	if (argc == 6)
	{
		data->c_must_eat = ft_atoi_ovf(argv[5]);
		data->c_eat_count = 1;
	}
	return (data);
}

static int	init_arg(char **argv, int argc)
{
	int	i;

	if (argc < 5)
		ft_exit_error("too low arguments");
	if (argc > 6)
		ft_exit_error("too many arguments");
	i = 1;
	while (i < argc)
	{
		ft_atoi_ovf(argv[i]);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	t_data			*data;
	int				status;
	int				i;

	if (!init_arg(argv, argc))
		return (1);
	data = init_struct(argv, argc);
	if (data == NULL)
		ft_malloc_error();
	i = -1;
	while (++i < data->max_size)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			philo_create(data, i);
	}
	i = 0;
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec > data->t_start.tv_sec \
		|| (time.tv_sec == data->t_start.tv_sec && time.tv_usec > data->t_start.tv_usec))
			break ;
		usleep(100);
	}
	while (i < data->max_size)
	{
		sem_post(data->c_sync);
		i++;
	}
	i = 0;
	while (i < data->max_size)
	{
		int val = 0;
		val = waitpid(0, &status, 0);
		if (val < 0)
		{
			kill(0, SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(data->forks);
	sem_close(data->c_dead);
	sem_close(data->c_print);
	sem_close(data->c_sync);
	exit(0);
}
