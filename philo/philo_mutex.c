/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:04:45 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/31 10:45:17 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	ptr->m_dead = &data->m_dead;
	ptr->m_print = &data->m_print;
	ptr->print = &data->print;
	ptr->c_must_eat = 0;
	pthread_mutex_init(&ptr->m_eat, NULL);
	ptr->is_dead = &data->is_dead;
	ptr->max_size = data->max_size;
	if (argc > 5)
		ptr->c_must_eat = ft_atoi_ovf(args[3]);
	return (ptr);
}

void	init_mutex(t_data *data, char **argv, int argc)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	while (i < data->max_size)
	{
		pthread_mutex_init(&data->m_forks[i], NULL);
		data->datas[i] = init_thread(data, &argv[2], argc, i);
		if (data->datas[i] == NULL)
			ft_malloc_error();
		data->forks[i++] = 0;
	}
}
