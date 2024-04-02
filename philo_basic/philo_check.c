/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:49:07 by inchoi            #+#    #+#             */
/*   Updated: 2023/09/08 12:17:12 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_info.h"

static int	monitor_eatnum(t_box *tools, t_philo *philo)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	pthread_mutex_lock(&tools->eating_mutex);
	while (i < tools->total_philo)
	{
		if (philo[i].eating_num >= tools->total_eat)
			flag++;
		i++;
	}
	if (flag == tools->total_philo)
	{
		pthread_mutex_lock(&tools->died_flag_mutex);
		tools->died_flag = 1;
		pthread_mutex_unlock(&tools->died_flag_mutex);
		pthread_mutex_unlock(&tools->eating_mutex);
		return (1);
	}
	pthread_mutex_unlock(&tools->eating_mutex);
	return (0);
}

static int	is_dead(t_box *tools, t_philo *philo)
{
	pthread_mutex_lock(&tools->eating_mutex);
	if (get_time() - philo->last_eat >= tools->time_to_die)
	{
		pthread_mutex_unlock(&tools->eating_mutex);
		return (1);
	}
	pthread_mutex_unlock(&tools->eating_mutex);
	return (0);
}

static int	monitor_clock(t_box *tools, t_philo *philo, int *idx)
{
	int	i;

	i = 0;
	while (i < tools->total_philo)
	{
		if (is_dead(tools, &philo[i]))
		{
			pthread_mutex_lock(&tools->died_flag_mutex);
			tools->died_flag = 1;
			(*idx) = i;
			pthread_mutex_unlock(&tools->died_flag_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	philo_monitor(t_box *tools, t_philo *philo)
{
	int		died;
	long	cur_time;
	long	time_now;

	while (1)
	{
		if (monitor_eatnum(tools, philo))
			break ;
		if (monitor_clock(tools, philo, &died))
		{
			cur_time = get_time();
			time_now = cur_time - tools->init_point;
			printf("%ld %d died\n", time_now, philo[died].id);
			break ;
		}
		usleep(100);
	}
}

int	philo_check(t_box *tools)
{
	pthread_mutex_lock(&tools->died_flag_mutex);
	if (tools->died_flag == 1)
	{
		pthread_mutex_unlock(&tools->died_flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&tools->died_flag_mutex);
	return (0);
}
