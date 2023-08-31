/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:49:07 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/28 19:49:08 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_info.h"

static void	multi_mutex(t_box *tools, int order)
{
	if (order == LOCK)
	{
		pthread_mutex_lock(&tools->eating_mutex);
		pthread_mutex_lock(&tools->flag_mutex);
	}
	else if (order == UNLOCK)
	{
		pthread_mutex_unlock(&tools->flag_mutex);
		pthread_mutex_unlock(&tools->eating_mutex);
	}
}

static void	print_died(t_box *tools, t_philo *philo, int died)
{
	pthread_mutex_lock(&tools->flag_mutex);
	if (tools->died_flag)
		thread_print(&philo[died], "died");
	pthread_mutex_unlock(&tools->flag_mutex);
}

void	philo_monitor(t_box *tools, t_philo *philo)
{
	int	i;
	int	died;

	died = -1;
	while (1)
	{
		i = -1;
		while (++i < tools->total_philo)
		{
			multiple_lock(tools);
			if ((philo[i].eating_num >= tools->total_eat) || \
					(get_time() - philo[i].last_eat >= tools->time_to_die))
			{
				tools->died_flag = 1;
				multiple_unlock(tools);
				died = i;
				print_died(tools, philo, died);
				break ;
			}
			multiple_unlock(tools);
		}
		if (died != -1)
			break ;
	}
}

void	thread_print(t_philo *thread, char *str)
{
	t_box	*tools;
	long	cur_time;
	long	time_now;

	tools = thread->tools;
	pthread_mutex_lock(&tools->print_mutex);
	cur_time = get_time();
	time_now = cur_time - tools->init_point;
	printf("%ld %d %s\n", time_now, thread->id, str);
	pthread_mutex_unlock(&tools->print_mutex);
}

int	check_died(t_box *tools)
{
	pthread_mutex_lock(&tools->flag_mutex);
	if (tools->died_flag == 1)
	{
		pthread_mutex_unlock(&tools->flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&tools->flag_mutex);
	return (0);
}

