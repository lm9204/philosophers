/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:31 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/20 19:44:26 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	int				eat;
	int				sleep;
	int				die;
}	t_data;

long long	ft_atoi_ovf(char *str);
void		ft_exit_error(char *str);

#endif