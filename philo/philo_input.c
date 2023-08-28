#include "philo_info.h"

static int  set_tools(t_box *tools, int ac, char **av)
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
    tools->init_point = 0;
    return (0);
}

static int  set_mutex(t_box *tools)
{
    int i;

    if (pthread_mutex_init(&(tools->eating_mutex), NULL))
        return (1);
    if (pthread_mutex_init(&(tools->print_mutex), NULL))
        return (1);
    tools->fork = malloc(sizeof(pthread_mutex_t) * tools->total_philo);
    if (!(tools->fork))
        return (1);
    i = 0;
    while (i < tools->total_philo)
    {
        if (pthread_mutex_init(&(tools->fork[i]), NULL))
            return (1);
        i++;
    }
    return (0);
}

static int  set_philo(t_box *tools)
{
    int i;

    tools->philo = malloc(sizeof(t_philo) * tools->total_philo);
    if (!tools->philo)
        return (1);
    i = 0;
    while (i < tools->total_philo)
    {
        tools->philo[i].id = i;
        tools->philo[i].left = i;
        tools->philo[i].right = (i + 1) % tools->total_philo;
        tools->philo[i].eating_num = 0;
        tools->philo[i].last_eat = 0;
        tools->philo[i].tools = tools;
        i++;
    }
    return (0);
}

int  philo_input(t_box *tools, int ac, char **av)
{
    if (set_tools(tools, ac, av))
        return (1);
    if (set_mutex(tools))
        return (1);
    if (set_philo(tools))
        return (1);
    return (0);
}
