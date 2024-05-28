/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:37 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/28 15:06:58 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eat_count(t_data *data, int f_eat_arg)
{
	int	i;

	i = 0;
	if (f_eat_arg <= 5)
		return (1);
	while (i < data->max_size)
	{
		pthread_mutex_lock(&data->datas[i]->c_eat);
		if (data->datas[i]->c_must_eat != 0)
		{
			pthread_mutex_unlock(&data->datas[i]->c_eat);
			return (1);
		}
		pthread_mutex_unlock(&data->datas[i]->c_eat);
		i++;
	}
	return (0);
}

static t_data	*init_struct(char **argv, int argc)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->threads = malloc(sizeof(pthread_t) * ft_atoi_ovf(argv[1]));
	data->m_forks = malloc(sizeof(pthread_mutex_t) * ft_atoi_ovf(argv[1]));
	data->forks = malloc(sizeof(int) * ft_atoi_ovf(argv[1]));
	data->datas = malloc(sizeof(t_th_data *) * (ft_atoi_ovf(argv[1])));
	if (!data->threads || !data->m_forks || !data->forks || !data->datas)
		return (NULL);
	gettimeofday(&data->t_start, NULL);
	data->is_dead = 0;
	data->print = 0;
	data->max_size = ft_atoi_ovf(argv[1]);
	init_mutex(data, argv, argc);
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
		pthread_create(&data->threads[i], NULL, \
		routine, (void *)data->datas[i]);
	while (check_eat_count(data, argc))
	{
		pthread_mutex_lock(&data->c_lock);
		if (data->is_dead)
		{
			pthread_mutex_unlock(&data->c_lock);
			break ;
		}
		pthread_mutex_unlock(&data->c_lock);
		usleep(200);
	}
	clear_threads(data);
	exit(0);
}
