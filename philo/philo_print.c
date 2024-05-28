/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:37:07 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/28 14:56:52 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_th_data *thread)
{
	struct timeval	time;

	check_printable(thread);
	gettimeofday(&time, NULL);
	printf("%lld %d is eating\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	pthread_mutex_unlock(thread->c_print);
}

void	p_getfork(t_th_data *thread)
{
	struct timeval	time;

	check_printable(thread);
	gettimeofday(&time, NULL);
	printf("%lld %d has taken a fork\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	pthread_mutex_unlock(thread->c_print);
}

void	p_sleep(t_th_data *thread)
{
	struct timeval	time;

	check_printable(thread);
	gettimeofday(&time, NULL);
	printf("%lld %d is sleeping\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	pthread_mutex_unlock(thread->c_print);
}

void	p_think(t_th_data *thread)
{
	struct timeval	time;

	check_printable(thread);
	gettimeofday(&time, NULL);
	printf("%lld %d is thinking\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	pthread_mutex_unlock(thread->c_print);
}

void	p_die(t_th_data *thread)
{
	struct timeval	time;

	check_printable(thread);
	*thread->print = 1;
	gettimeofday(&time, NULL);
	printf("%lld %d died\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	pthread_mutex_unlock(thread->c_print);
}
