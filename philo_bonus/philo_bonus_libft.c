/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:53:34 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/08 18:03:45 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus_info.h"

static char	*ft_strdup(char *src)
{
	char	*arr;
	int		size;
	int		i;

	size = ft_strlen(src) - 1;
	arr = (char *)malloc(sizeof(char) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static int	find_size(long long n)
{
	int	size;

	size = 0;
	if (n <= 0)
	{
		size++;
		n = -n;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*put(char *newarr, int n, int size)
{
	newarr[size--] = '\0';
	while (n > 0)
	{
		newarr[size--] = (n % 10) + '0';
		n /= 10;
	}
	return (newarr);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*newarr;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = find_size((long long) n);
	newarr = (char *)malloc((size + 1) * sizeof(char));
	if (!newarr)
		return (0);
	if (n < 0)
	{
		newarr[0] = '-';
		n *= -1;
	}
	return (put(newarr, n, size));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)malloc(size * sizeof(char));
	if (!joined)
		return (0);
	while (i < size && *s1 != '\0')
	{
		joined[i++] = *s1;
		s1++;
	}
	while (i < size && *s2 != '\0')
	{
		joined[i++] = *s2;
		s2++;
	}
	joined[i] = '\0';
	return (joined);
}
