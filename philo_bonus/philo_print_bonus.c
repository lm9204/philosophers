/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:37:07 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/28 12:04:10 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	p_eat(t_th_data *thread)
{
	struct timeval	time;

	sem_wait(thread->s_print);
	gettimeofday(&time, NULL);
	printf("%lld %d is eating\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	sem_post(thread->s_print);
}

void	p_getfork(t_th_data *thread)
{
	struct timeval	time;

	sem_wait(thread->s_print);
	gettimeofday(&time, NULL);
	printf("%lld %d has taken a fork\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	sem_post(thread->s_print);
}

void	p_sleep(t_th_data *thread)
{
	struct timeval	time;

	sem_wait(thread->s_print);
	gettimeofday(&time, NULL);
	printf("%lld %d is sleeping\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	sem_post(thread->s_print);
}

void	p_think(t_th_data *thread)
{
	struct timeval	time;

	sem_wait(thread->s_print);
	gettimeofday(&time, NULL);
	printf("%lld %d is thinking\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	sem_post(thread->s_print);
}

void	p_die(t_th_data *thread)
{
	struct timeval	time;

	sem_wait(thread->s_print);
	gettimeofday(&time, NULL);
	printf("%lld %d died\n", \
	t_calc(&time, &thread->t_start), thread->index + 1);
	sem_post(thread->s_print);
}
