/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:56:02 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/20 17:58:28 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
	|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

long long	ft_atoi_ovf(char *str)
{
	long long	prev;
	long long	res;
	long long	sign;
	int			i;

	sign = 1;
	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			ft_exit_error(str);
		prev = res;
		res *= 10;
		res += (str[i] - 48) * sign;
		if ((res % 10) != (str[i] - 48) * sign || (res / 10 != prev))
			ft_exit_error(str);
		i++;
	}
	return (res);
}

void	ft_exit_error(char *str)
{
	printf("philosophers: %s\n", str);
	exit(1);
}
