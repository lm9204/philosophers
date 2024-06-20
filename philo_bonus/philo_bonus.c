/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:37 by yeondcho          #+#    #+#             */
/*   Updated: 2024/06/18 14:58:27 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_start_time(struct timeval *t_start, int milliseconds)
{
	int	microseconds;

	microseconds = milliseconds * 1000 + 50000;
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
	init_sem(data);
	if (!data->forks || !data->s_dead || !data->s_print || !data->pids \
	|| !data->s_sync || !data->s_t_last || !data->s_done)
		return (NULL);
	gettimeofday(&data->t_start, NULL);
	init_start_time(&data->t_start, data->max_size);
	data->t_die = ft_atoi_ovf(argv[2]);
	data->t_eat = ft_atoi_ovf(argv[3]);
	data->t_sleep = ft_atoi_ovf(argv[4]);
	data->eat_count = 0;
	data->f_eatcount = 0;
	if (argc == 6)
	{
		data->eat_count = ft_atoi_ovf(argv[5]);
		data->f_eatcount = 1;
	}
	return (data);
}

static int	init_arg(char **argv, int argc)
{
	int	i;
	int	val;

	if (argc < 5)
		ft_exit_error("too low arguments");
	if (argc > 6)
		ft_exit_error("too many arguments");
	i = 1;
	while (i < argc)
	{
		val = ft_atoi_ovf(argv[i]);
		if (val <= 0)
			ft_exit_error(argv[i]);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (!init_arg(argv, argc))
		return (1);
	data = init_struct(argv, argc);
	if (data == NULL)
		ft_malloc_error();
	i = -1;
	while (++i < data->max_size)
		sem_wait(data->s_done);
	i = -1;
	while (++i < data->max_size)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			philo_create(data, i);
	}
	start_sync(data);
	wait_philo(data);
	clear_philo(data);
	exit(0);
}
