/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:44:27 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/06 14:58:48 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus_info.h"

int	ft_error(char *str)
{
	while (*str != '\0')
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
	exit(1);
	return (1);
}

static int	figure_long(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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
