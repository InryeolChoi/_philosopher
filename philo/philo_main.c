#include "philo_info.h"

static int  check_av(int ac, char **av)
{
    int     i;
    int     x;

    i = 1;
    if (ac < 5 || ac > 6)
        return (0);
    while (i < ac)
    {
        x = 0;
        if (av[i][x] == '-')
            return (0);
        while (av[i][x] >= '0' && av[i][x] <= '9')
            x++;
        if (av[i][x] != '\0')
            return (0);
        i++;
    }
    return (1);
}

static t_box    *set_tools(int ac, char **av)
{
    t_box   *tools;

    tools = (t_box *)malloc(sizeof(t_box));
    if (!tools)
        return (0);
    tools->philo_num = ft_atoi(av[1]);
    tools->survival_time = ft_atoi(av[2]);
    tools->eating_time = ft_atoi(av[3]);
    tools->sleep_time = ft_atoi(av[4]);
    if (tools->philo_num <= 0 || tools->survival_time <= 0 \
        || tools->eating_time <= 0 || tools-> sleep_time <= 0)
        return (0);
    else if (tools->philo_num > INT_MAX || tools->survival_time > INT_MAX \
        || tools->eating_time > INT_MAX || tools-> sleep_time > INT_MAX)
        return (0);
    if (ac == 6)
    {
        tools->eating_num = ft_atoi(av[5]);
        if (tools->eating_num <= 0 || tools->eating_num > INT_MAX)
            return (0);
    }
    else
        tools->eating_num = -1;
    tools->flag = 0;
    return (tools);
}

static t_philo **set_philo(t_box *tools)
{
    int     i;
    t_philo **philo;

    i = 0;
    philo = (t_philo **)malloc(sizeof(t_philo *) * tools->philo_num);
    if (!philo)
        return (fail_alloc_philo(philo, i));
    while (i < tools->philo_num)
    {
        philo[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!philo[i])
            return (fail_alloc_philo(philo, i));
        philo[i]->id = i + 1;
        philo[i]->eat_count = 0;
        philo[i]->left = i;
        philo[i]->right = (i + 1) % tools->philo_num;
        philo[i]->last_eat = 0;
        philo[i]->last_time = 0;
        philo[i]->tools = tools;
        i++;
    }
    return (philo);
}

int main(int ac, char **av)
{
    t_box   *tools;
    t_philo **philo;

    if (check_av(ac, av) == 0)
        return (ft_error("wrong inputs"));
    tools = set_tools(ac, av);
    if (!tools)
        return (1);
    philo = set_philo(tools);
    if (!philo)
        return (1);
    philo_execute(tools, philo);
}