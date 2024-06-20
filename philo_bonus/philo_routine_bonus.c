/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:16:44 by yeondcho          #+#    #+#             */
/*   Updated: 2024/06/18 14:54:31 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	choose_fork(t_th_data *thread)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		sem_wait(thread->forks);
		if (!calc_last_time(thread))
			return (0);
		p_getfork(thread);
		i++;
	}
	return (1);
}

int	get_forks(t_th_data *thread)
{
	if (!choose_fork(thread))
		return (0);
	p_eat(thread);
	sem_wait(thread->s_t_last);
	gettimeofday(&thread->t_last_meal, NULL);
	sem_post(thread->s_t_last);
	spend_time(thread, thread->t_eat * 1000);
	drop_forks(thread);
	sem_wait(thread->s_count);
	if (thread->eat_count > 0)
		thread->eat_count--;
	sem_post(thread->s_count);
	return (1);
}

int	drop_forks(t_th_data *thread)
{
	sem_post(thread->forks);
	sem_post(thread->forks);
	return (1);
}

void	*routine(void *arg)
{
	t_th_data	*ptr;

	ptr = (t_th_data *)arg;
	sem_wait(ptr->s_sync);
	p_think(ptr);
	if (ptr->max_size > 1 && ptr->index % 2 == 0)
		spend_time(ptr, ptr->t_eat * 1000);
	if (ptr->max_size > 2 && ptr->max_size % 2 == 1 && ptr->index == 0)
		spend_time(ptr, ptr->t_eat * 1000);
	while (1)
	{
		if (!calc_last_time(ptr) || !get_forks(ptr))
			break ;
		p_sleep(ptr);
		spend_time(ptr, ptr->t_sleep * 1000);
		if (!calc_last_time(ptr))
			break ;
		p_think(ptr);
	}
	return (NULL);
}
