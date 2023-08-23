#include "philo_info.h"

static int  set_tools(t_box **tools, int ac, char **av)
{
    (*tools)->philo_num = ft_atoi(av[1]);
    (*tools)->survival_time = ft_atoi(av[2]);
    (*tools)->eating_time = ft_atoi(av[3]);
    (*tools)->sleep_time = ft_atoi(av[4]);
    if ((*tools)->philo_num <= 0 || (*tools)->survival_time <= 0 \
        || (*tools)->eating_time <= 0 || (*tools)-> sleep_time <= 0)
        return (1);
    if (ac == 6)
    {
        (*tools)->eating_num = ft_atoi(av[5]);
        if ((*tools)->eating_num <= 0)
            return (1);
    }
    else
        (*tools)->eating_num = 0;
    (*tools)->flag = 0;
    return (0);
}

t_philo **set_philo(t_philo **philo, t_box *tools)
{
    int i;

    i = 0;
    while (i < tools->philo_num)
    {
        philo[i]->id = i + 1;
        philo[i]->eat_count = 0;
        philo[i]->left = i;
        philo[i]->right = (i + 1) % tools->philo_num;
        philo[i]->tools = tools;
        i++;
    }
    return (philo);
}

int main(int ac, char **av)
{
    t_box   *tools;
    t_philo **philo;

    if (ac < 5 || ac > 6)
        return (ft_error("wrong inputs"));
    if (set_tools(&tools, ac, av) == 1)
        return (1);
    philo = (t_philo **)malloc(sizeof(t_philo *) * tools->philo_num);
    if (!philo)
        return (1);
    philo = set_philo(philo, tools);
}