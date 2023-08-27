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

void    thread_print(t_philo *thread, char *str)
{
    t_box   *tools;
    long    time_now;

    tools = thread->tools;
    pthread_mutex_lock(&tools->write);
    time_now = get_time() - tools->init_point;
    printf("%ld %d %s\n", time_now, thread->id, str);
    pthread_mutex_unlock(&tools->write);
}
