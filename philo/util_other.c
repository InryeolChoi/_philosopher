/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:33:03 by inchoi            #+#    #+#             */
/*   Updated: 2023/10/31 19:58:23 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_info.h"

static int	figure_long(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] >= 9 && str[i] <= 13)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (num >= 922337203685477580 || \
				(num == 922337203685477580 - 1 && num % 10 > 7))
			return (figure_long(sign));
		num = (num * 10 + str[i] - '0');
		i++;
	}
	return ((int)(sign * num));
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	arg_usleep(t_box *tools)
{
	if (tools->time_to_die < 2 * tools->time_to_eat)
		return (tools->time_to_die * 500);
	else
		return (tools->time_to_eat * 100);
}
