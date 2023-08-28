/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:38:25 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/28 19:39:27 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_info.h"

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

int	arg_usleep(t_box *tools)
{
	if (tools->time_to_die < 2 * tools->time_to_eat)
		return (tools->time_to_die * 500);
	else
		return (tools->time_to_eat * 100);
}
