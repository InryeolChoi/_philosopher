#include "philo_info.h"

static int  set_tools(t_box *tools, int ac, char **av)
{
    tools->philo_num = ft_atoi(av[1]);
    tools->survival_time = ft_atoi(av[2]);
    tools->eating_time = ft_atoi(av[3]);
    tools->sleep_time = ft_atoi(av[4]);
    if (tools->philo_num <= 0 || tools->survival_time <= 0 \
        || tools->eating_time <= 0 || tools-> sleep_time <= 0)
        return (1);
    else if (tools->philo_num > INT_MAX || tools->survival_time > INT_MAX \
        || tools->eating_time > INT_MAX || tools-> sleep_time > INT_MAX)
        return (1);
    if (ac == 6)
    {
        tools->eating_num = ft_atoi(av[5]);
        if (tools->eating_num <= 0 || tools->eating_num > INT_MAX)
            return (1);
    }
    else
        tools->eating_num = -1;
    tools->flag = 0;
    return (0);
}

static int  set_mutex(t_box *tools)
{

    tools->philo = (t_philo *)malloc(sizeof(t_philo) * tools->philo_num);
    if (!tools->philo)
        return (1);
    return (0);
}


static int  *set_philo(t_box *tools)
{

}

static int  set_input(t_box *tools, int ac, char **av)
{
    if (!set_tools(tools, ac, av))
        return (1);
    if (!set_mutex(tools))
        return (1);
    if (!set_philo(tools))
        return (1);
    return (0);
}
