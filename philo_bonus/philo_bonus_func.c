#include "philo_bonus_info.h"

void	philo_grep_fork(t_box *tools)
{
	sem_wait(tools->fork);
	philo_print(tools, tools->philo_id, "has taken a fork");
	sem_wait(tools->fork);
	philo_print(tools, tools->philo_id, "has taken a fork");
}

void	philo_eat_food(t_box *tools)
{
	long	cur_time;
	long	eat_start;

	philo_print(tools, tools->philo_id, "is eating");
	tools->eat_count++;
	eat_start = get_time();
	while (1)
	{
		cur_time = get_time();
		if (cur_time - eat_start >= tools->time_to_eat)
			break;
		usleep(100);
	}
	sem_post(tools->fork);
	sem_post(tools->fork);
}

void	philo_sleep(t_box *tools)
{
	long	cur_time;
	long	start_sleep;

	start_sleep = get_time();
	philo_print(tools, tools->philo_id, "is thinking");
	while (1)
	{
		cur_time = get_time();
		if (cur_time - start_sleep >= tools->time_to_sleep)
			break ;
		usleep(1000);
	}
	philo_print(tools, tools->philo_id, "is thinking");
}

int	philo_print(t_box *tools, int philo_id, char *str)
{
	long	cur_time;
	long	time_now;

	sem_wait(tools->print);
	cur_time = get_time();
	time_now = cur_time - tools->init_point;
	printf("%ld ", time_now);
	printf("%d ", philo_id);
	printf("%s\n", str);
	sem_post(tools->print);
	return (0);
}
