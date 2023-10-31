#include "philo_bonus_info.h"

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
		tools->total_eat = INT_MAX;
	return (0);
}

static int	set_semaphore(t_box *tools)
{
	unlink("sem_fork");
	unlink("sem_print");
	unlink("sem_died");
	tools->fork = sem_open("sem_fork", O_CREAT, 0644, tools->total_philo);
	tools->print = sem_open("sem_print", O_CREAT, 0644, 1);
	tools->died = sem_open("sem_died", O_CREAT, 0644, 1);
	if (tools->fork == SEM_FAILED || tools->print == SEM_FAILED || \
		tools->died == SEM_FAILED)
		return (1);
	return (0);
}

int	bonus_input(t_box *tools, int ac, char **av)
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