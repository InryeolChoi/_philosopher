/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:38:25 by inchoi            #+#    #+#             */
/*   Updated: 2023/10/31 19:58:13 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_info.h"

int	philo_print(t_philo *thread, char *str)
{
	t_box	*tools;
	long	cur_time;
	long	time_now;

	tools = thread->tools;
	pthread_mutex_lock(&tools->died_flag_mutex);
	pthread_mutex_lock(&tools->print_mutex);
	cur_time = get_time();
	time_now = cur_time - tools->init_point;
	if (tools->died_flag == 0)
		printf("%ld %d %s\n", time_now, thread->id, str);
	pthread_mutex_unlock(&tools->print_mutex);
	pthread_mutex_unlock(&tools->died_flag_mutex);
	return (0);
}

int	philo_single(t_box *tools, t_philo *thread)
{
	int		i;
	long	cur_time;
	long	time_now;

	cur_time = get_time();
	time_now = cur_time - tools->init_point;
	printf("%ld %d has taken a fork\n", time_now, thread->id);
	usleep(tools->time_to_die * 1000);
	time_now = get_time() - tools->init_point;
	printf("%ld %d died", time_now, thread->id);
	i = 0;
	while (i < tools->total_philo)
		pthread_mutex_destroy(&tools->fork_mutex[i++]);
	free(tools->fork_mutex);
	free(tools->fork);
	free(tools->philo);
	pthread_mutex_destroy(&tools->print_mutex);
	pthread_mutex_destroy(&tools->eating_mutex);
	pthread_mutex_destroy(&tools->died_flag_mutex);
	pthread_mutex_destroy(&tools->start_mutex);
	return (0);
}

void	philo_free(t_box *tools)
{
	int	i;

	i = 0;
	while (i < tools->total_philo)
		pthread_join(tools->philo[i++].thread_id, NULL);
	i = 0;
	while (i < tools->total_philo)
		pthread_mutex_destroy(&tools->fork_mutex[i++]);
	free(tools->fork_mutex);
	free(tools->fork);
	free(tools->philo);
	pthread_mutex_destroy(&tools->print_mutex);
	pthread_mutex_destroy(&tools->eating_mutex);
	pthread_mutex_destroy(&tools->died_flag_mutex);
	pthread_mutex_destroy(&tools->start_mutex);
}
