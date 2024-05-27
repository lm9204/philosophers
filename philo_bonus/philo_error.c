/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:17:58 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/22 20:18:44 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_error(char *str)
{
	printf("philosophers: invaild arguments: %s\n", str);
	exit(1);
}

void	ft_malloc_error(void)
{
	printf("philosophers: malloc error\n");
	exit(1);
}
