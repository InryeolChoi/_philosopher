#include "philo_bonus_info.h"

int philo_execute(t_box	*tools)
{
	int i;

	i = 0;
	while (i < tools->total_philo)
	{
		tools->pid_box[i] = fork();
		if (tools->pid_box[i] == 0)
		{
			tools->philo_id = i + 1;
			tools->eat_count = 0;
			tools->init_point = get_time();
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
	int	philo;
	int status;

	while (i < tools->total_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			philo = 0;
			while (philo < tools->total_philo)
			{
				kill(tools->pid_box[philo], SIGKILL);
				philo++;
			}
		}
		i++;
	}
	return (philo_free(tools));
}

int	philo_free(t_box *tools)
{
	sem_close(tools->print);
	sem_close(tools->fork);
	sem_close(tools->died);
	sem_unlink("sem_print");
	sem_unlink("sem_fork");
	sem_unlink("sem_died");
	free(tools->pid_box);
	return (0);
}

void	philo_child(t_box *tools)
{
	void	*select;

	select = (void *)tools;
	if (pthread_create(&(tools->monitor_thread), NULL, &monitor_thread, select))
		exit (1);
	if (tools->philo_id % 2 == 0)
		usleep(200);
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
	long	cur_time;

	tools = (t_box *)arg;
	while (1)
	{
		cur_time = get_time();
		sem_wait(tools->died);
		if (cur_time - tools->init_point >= tools->time_to_die)
		{
			philo_print(tools, tools->philo_id, "is died");
			exit(1);
		}
		if (tools->total_eat != -1 && tools->eat_count == tools->total_eat)
		{
			philo_print(tools, tools->philo_id, "is died");
			exit(1);
		}
		sem_post(tools->died);
		usleep(100);
	}
	return (arg);
}
