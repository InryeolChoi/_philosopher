/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:44:04 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/08 19:01:08 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus_info.h"

int	philo_single(t_box *tools)
{
	long	time_now;

	tools->philo_id = 1;
	time_now = get_time() - tools->init_point;
	printf("%ld %d has taken a fork\n", time_now, tools->philo_id);
	usleep(tools->time_to_die * 1000);
	time_now = get_time() - tools->init_point;
	printf("%ld %d died\n", time_now, tools->philo_id);
	return (0);
}

int	philo_execute(t_box	*tools)
{
	int	i;

	i = 0;
	tools->init_point = get_time();
	sem_wait(tools->lasteat_sem);
	tools->last_eat = tools->init_point;
	sem_post(tools->lasteat_sem);
	if (tools->total_philo == 1)
		return (philo_single(tools));
	while (i < tools->total_philo)
	{
		tools->pid_box[i] = fork();
		if (tools->pid_box[i] == 0)
		{
			tools->philo_id = i + 1;
			tools->eat_count = 0;
			philo_child(tools);
		}
		else if (tools->pid_box[i] == -1)
			return (1);
		else
			i++;
	}
	return (philo_parent(tools));
}

int	philo_parent(t_box *tools)
{
	int	i;
	int	count;
	int	exit_code;
	int	status;

	i = 0;
	count = 0;
	while (i < tools->total_philo)
	{
		waitpid(-1, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			return (philo_kill(tools, exit_code));
		i++;
	}
	return (0);
}

int	philo_kill(t_box *tools, int exit_code)
{
	int	i;

	i = 0;
	while (i < tools->total_philo)
		kill(tools->pid_box[i++], SIGKILL);
	if (exit_code == -1)
		printf("sem fail\n");
	return (0);
}
