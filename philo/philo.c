/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:37 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/23 11:00:12 by yeondcho         ###   ########.fr       */
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

static t_th_data	*init_thread(t_data *data, char **args, int argc, int index)
{
	t_th_data	*ptr;

	ptr = malloc(sizeof(t_th_data));
	if (ptr == NULL)
		return (NULL);
	ptr->index = index;
	init_time(&ptr->t_last_meal, NULL);
	init_time(&ptr->t_start, &data->t_start);
	ptr->t_die = ft_atoi_ovf(args[0]);
	ptr->t_eat = ft_atoi_ovf(args[1]);
	ptr->t_sleep = ft_atoi_ovf(args[2]);
	ptr->m_left = &data->m_forks[index];
	ptr->m_right = &data->m_forks[(index + 1) % data->max_size];
	ptr->left = &data->forks[index];
	ptr->right = &data->forks[(index + 1) % data->max_size];
	ptr->c_lock = &data->c_lock;
	ptr->c_print = &data->c_print;
	ptr->c_must_eat = 0;
	pthread_mutex_init(&ptr->c_eat, NULL);
	ptr->is_dead = &data->is_dead;
	ptr->max_size = data->max_size;
	if (argc > 5)
		ptr->c_must_eat = ft_atoi_ovf(args[3]);
	return (ptr);
}

static t_data	*init_struct(char **argv, int argc, int i)
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
	data->max_size = ft_atoi_ovf(argv[1]);
	pthread_mutex_init(&data->c_lock, NULL);
	pthread_mutex_init(&data->c_print, NULL);
	while (i < data->max_size)
	{
		pthread_mutex_init(&data->m_forks[i], NULL);
		data->datas[i] = init_thread(data, &argv[2], argc, i);
		if (data->datas[i] == NULL)
			return (NULL);
		data->forks[i++] = 0;
	}
	return (data);
}

static int	init_arg(char **argv, int argc)
{
	int	i;

	if (argc < 5)
	{
		printf("too low args\n");
		return (0);
	}
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
	t_data	*data;
	int		i;

	if (!init_arg(argv, argc))
		return (1);
	data = init_struct(argv, argc, 0);
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
		usleep(100);
	}
	clear_threads(data);
	return (0);
}
