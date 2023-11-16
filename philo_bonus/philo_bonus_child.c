/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:12:17 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/08 19:59:16 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus_info.h"

void	philo_child(t_box *tools)
{
	void	*select;

	tools->semname_died = ft_strjoin("died_", ft_itoa(tools->philo_id));
	tools->semname_lasteat = ft_strjoin("lasteat_", ft_itoa(tools->philo_id));
	tools->semname_eatcnt = ft_strjoin("eatcnt_", ft_itoa(tools->philo_id));
	sem_unlink(tools->semname_died);
	sem_unlink(tools->semname_lasteat);
	sem_unlink(tools->semname_eatcnt);
	tools->died = sem_open(tools->semname_died, O_CREAT, 0644, 1);
	tools->lasteat_sem = sem_open(tools->semname_lasteat, O_CREAT, 0644, 1);
	tools->eatcnt_sem = sem_open(tools->semname_eatcnt, O_CREAT, 0644, 1);
	if (tools->died == SEM_FAILED || tools->lasteat_sem == SEM_FAILED || \
		tools->eatcnt_sem == SEM_FAILED)
		exit (-1);
	select = (void *)tools;
	if (pthread_create(&(tools->monitor_thread), NULL, &monitor_thread, select))
		exit (-1);
	while (1)
	{
		philo_grep_fork(tools);
		philo_eat_food(tools);
		philo_sleep(tools);
	}
}

void	*monitor_thread(void *arg)
{
	t_box	*tools;

	tools = (t_box *)arg;
	while (1)
	{
		sem_wait(tools->died);
		if (tools->total_eat != -1)
			monitor_thread_eatcnt(tools);
		monitor_thread_time(tools);
		sem_post(tools->died);
		usleep(100);
	}
	return (arg);
}

static void	clear_sem_for_process(t_box *tools)
{
	sem_close(tools->died);
	sem_close(tools->lasteat_sem);
	sem_close(tools->eatcnt_sem);
	sem_unlink(tools->semname_died);
	sem_unlink(tools->semname_lasteat);
	sem_unlink(tools->semname_eatcnt);
	free(tools->semname_died);
	free(tools->semname_lasteat);
	free(tools->semname_eatcnt);
}

void	monitor_thread_eatcnt(t_box *tools)
{
	sem_wait(tools->eatcnt_sem);
	if (tools->eat_count == tools->total_eat)
	{
		sem_post(tools->fork);
		sem_post(tools->fork);
		sem_post(tools->eatcnt_sem);
		sem_post(tools->died);
		clear_sem_for_process(tools);
		exit(0);
	}
	sem_post(tools->eatcnt_sem);
}

void	monitor_thread_time(t_box *tools)
{
	sem_wait(tools->lasteat_sem);
	if (get_time() - tools->last_eat >= tools->time_to_die)
	{
		sem_post(tools->lasteat_sem);
		sem_post(tools->died);
		clear_sem_for_process(tools);
		philo_print(tools, tools->philo_id, "died");
		exit(tools->philo_id);
	}
	sem_post(tools->lasteat_sem);
}
