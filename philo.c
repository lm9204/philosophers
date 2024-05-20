/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:37 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/20 19:14:17 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_thread(t_data *data, int argc, char **argv)
{
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
	data->threads = malloc(sizeof(pthread_t) * (ft_atoi_ovf(argv[1]) + 1));
	data->forks = malloc(sizeof(int) * ft_atoi_ovf(argv[1]));
	data->die = ft_atoi_ovf(argv[2]);
	data->eat = ft_atoi_ovf(argv[3]);
	data->sleep = ft_atoi_ovf(argv[4]);
}

void	routine()
{
	
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_thread(&data, argc, argv))
		return (1);

	return (0);
}

