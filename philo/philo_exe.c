/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:56:44 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/01 19:26:34 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_info.h"

static int	thread_fork(t_philo *philo, t_box *tools)
{
	pthread_mutex_lock(&tools->fork_mutex[philo->left]);
	tools->fork[philo->left] = 1;
	if (philo_check(tools))
	{
		tools->fork[philo->left] = 0;
		pthread_mutex_unlock(&tools->fork_mutex[philo->left]);
		return (1);
	}
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&tools->fork_mutex[philo->right]);
	tools->fork[philo->right] = 1;
	if (philo_check(tools))
	{
		tools->fork[philo->right] = 0;
		pthread_mutex_unlock(&tools->fork_mutex[philo->right]);
		tools->fork[philo->left] = 0;
		pthread_mutex_unlock(&tools->fork_mutex[philo->left]);
		return (1);
	}
	philo_print(philo, "has taken a fork");
	return (0);
}

static int	thread_eat(t_philo *philo, t_box *tools)
{
	long	eat_start;
	long	cur_time;

	if (thread_fork(philo, tools))
		return (1);
	pthread_mutex_lock(&tools->eating_mutex);
	philo_print(philo, "is eating");
	philo->eating_num += 1;
	eat_start = get_time();
	philo->last_eat = get_time();
	pthread_mutex_unlock(&tools->eating_mutex);
	while (1)
	{
		cur_time = get_time();
		if (cur_time - eat_start >= tools->time_to_eat)
			break ;
		usleep(100);
	}
	tools->fork[philo->right] = 0;
	pthread_mutex_unlock(&tools->fork_mutex[philo->right]);
	tools->fork[philo->left] = 0;
	pthread_mutex_unlock(&tools->fork_mutex[philo->left]);
	return (0);
}

static void	thread_sleep(t_philo *philo, t_box *tools)
{
	long	time_to_sleep;
	long	cur_time;
	long	start_sleep;

	time_to_sleep = tools->time_to_sleep;
	start_sleep = get_time();
	philo_print(philo, "is sleeping");
	while (1)
	{
		cur_time = get_time();
		if (cur_time - start_sleep >= time_to_sleep)
			break ;
		usleep(1000);
	}
}

static void	*threads_action(void *arg)
{
	t_box	*tools;
	t_philo	*thread;

	thread = (t_philo *)arg;
	tools = thread->tools;
	pthread_mutex_lock(&tools->start_mutex);
	pthread_mutex_unlock(&tools->start_mutex);
	if (thread->id % 2 == 0)
		usleep(arg_usleep(tools));
	while (!philo_check(tools))
	{
		if (thread_eat(thread, tools))
			break ;
		if (philo_check(tools))
			break ;
		thread_sleep(thread, tools);
		if (philo_check(tools))
			break ;
		philo_print(thread, "is thinking");
	}
	return (arg);
}

int	philo_execute(t_box *tools, t_philo *philo)
{
	int		i;
	void	*select;

	i = 0;
	if (tools->total_philo == 1)
	{
		tools->init_point = get_time();
		return (philo_single(tools, philo));
	}
	pthread_mutex_lock(&tools->start_mutex);
	while (i < tools->total_philo)
	{
		philo[i].philo_begin = get_time();
		philo[i].last_eat = get_time();
		select = (void *)&(philo[i]);
		if (pthread_create(&(philo[i].thread_id), NULL, threads_action, select))
			return (1);
		i++;
	}
	tools->init_point = get_time();
	pthread_mutex_unlock(&tools->start_mutex);
	philo_monitor(tools, philo);
	philo_free(tools);
	return (0);
}
