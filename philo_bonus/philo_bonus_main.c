/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:44:02 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/08 17:07:24 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus_info.h"

static int	check_av(int ac, char **av)
{
	int	i;
	int	x;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (i < ac)
	{
		x = 0;
		if (av[i][x] == '-')
			return (1);
		while (av[i][x] >= '0' && av[i][x] <= '9')
			x++;
		if (av[i][x] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static int	set_tools(t_box *tools, int ac, char **av)
{
	tools->total_philo = ft_atoi(av[1]);
	tools->time_to_die = ft_atoi(av[2]);
	tools->time_to_eat = ft_atoi(av[3]);
	tools->time_to_sleep = ft_atoi(av[4]);
	if (tools->total_philo <= 0 || tools->time_to_die <= 0 \
			|| tools->time_to_eat <= 0 || tools-> time_to_sleep <= 0)
		return (1);
	else if (tools->total_philo > INT_MAX || tools->time_to_die > INT_MAX \
			|| tools->time_to_eat > INT_MAX || tools-> time_to_sleep > INT_MAX)
		return (1);
	if (ac == 6)
	{
		tools->total_eat = ft_atoi(av[5]);
		if (tools->total_eat <= 0 || tools->total_eat > INT_MAX)
			return (1);
	}
	else
		tools->total_eat = -1;
	return (0);
}

static int	set_semaphore(t_box *tools)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	tools->fork = sem_open("sem_fork", O_CREAT, 0644, tools->total_philo);
	tools->print = sem_open("sem_print", O_CREAT, 0644, 1);
	if (tools->fork == SEM_FAILED || tools->print == SEM_FAILED)
		return (1);
	return (0);
}

static int	bonus_input(t_box *tools, int ac, char **av)
{
	if (set_tools(tools, ac, av))
		return (1);
	tools->pid_box = malloc(sizeof(int) * tools->total_philo);
	if (!tools->pid_box)
		return (1);
	if (set_semaphore(tools))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_box	tools;

	if (check_av(ac, av))
		return (ft_error("wrong input"));
	if (bonus_input(&tools, ac, av))
		return (ft_error("wrong input"));
	if (philo_execute(&tools))
		return (ft_error("malfunction"));
	sem_close(tools.print);
	sem_close(tools.fork);
	sem_unlink("sem_print");
	sem_unlink("sem_fork");
	free(tools.pid_box);
	return (0);
}
