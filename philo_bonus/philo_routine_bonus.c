/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:16:44 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/28 14:33:34 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	int	choose_fork(t_th_data *thread)
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
	sem_wait(thread->s_count);
	if (thread->eat_count > 0)
		thread->eat_count--;
	sem_post(thread->s_count);
	p_eat(thread);
	sem_wait(thread->s_t_last);
	gettimeofday(&thread->t_last_meal, NULL);
	sem_post(thread->s_t_last);
	spend_time(thread->t_eat);
	drop_forks(thread);
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
	int			c_loop;

	ptr = (t_th_data *)arg;
	p_think(ptr);
	if (ptr->max_size > 1 && ptr->index % 2 == 0)
		spend_time(ptr->t_eat);
	if (ptr->max_size > 2 && ptr->max_size % 2 == 1 && ptr->index == 0)
		spend_time(ptr->t_eat);
	c_loop = 1;
	if (ptr->eat_count > 0)
		c_loop = 0;
	while (c_loop || ptr->eat_count > 0)
	{
		if (!calc_last_time(ptr) || !get_forks(ptr))
			break ;
		p_sleep(ptr);
		spend_time(ptr->t_sleep);
		if (!calc_last_time(ptr))
			break ;
		p_think(ptr);
	}
	return (NULL);
}
