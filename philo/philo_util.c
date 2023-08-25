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

int ft_error(char *str)
{
    printf("%s", str);
    return (1);
}

void    philo_free(t_box *tools)
{
    int i;

    i = 0;
    while (i < tools->philo_num)
        pthread_mutex_destory(&tools->fork[i++]);
    free(tools->fork);
    free(tools->philo);
    pthread_mutex_destroy(&tools->eating);
    pthread_mutex_destroy(&tools->write);
}