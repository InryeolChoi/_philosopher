#include "philo_info.h"

static int	figure_long(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int ft_atoi(char *str)
{
    int     i;
    int     sign;
    long    num;

    i = 0;
    sign = 1;
    num = 0;
    while (str[i] >= 9 && str[i] <= 13)
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        if (num >= 922337203685477580 || \
        (num == 922337203685477580 - 1 && num % 10 > 7))
			return (figure_long(sign));
        num = (num * 10 + str[i] - '0');
        i++;
    }
    return ((int)(sign * num));
}

long    get_time(void)
{
    struct  timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    thread_print(t_philo *thread, char *str)
{
    t_box   *tools;
    long    cur_time;
    long    time_now;

    tools = thread->tools;
    pthread_mutex_lock(&tools->print_mutex);
    cur_time = get_time();
    time_now = cur_time - tools->init_point;
    printf("%ld %d %s\n", time_now, thread->id, str);
    pthread_mutex_unlock(&tools->print_mutex);
}

int check_died(t_box *tools)
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
