#include "philo_info.h"

int ft_error(char *str)
{
    printf("%s", str);
    return (1);
}

static int  check_av(int ac, char **av)
{
    int i;
    int x;

    i = 1;
    if (ac < 5 || ac > 6)
        return (1);
    while (i < ac)
    {
        x = 0;
        if (av[i][x] == '-')
            return (1);
        while (av[i][x] >= '0' && av[i][x] <= '9')
            x++;
        if (av[i][x] != '\0')
            return (1);
        i++;
    }
    return (0);
}

int main(int ac, char **av)
{
    t_box   tools;

    if (check_av(ac, av))
        return (ft_error("wrong inputs"));
    if (philo_input(&tools, ac, av))
        return (ft_error("wrong inputs"));
    if (philo_execute(&tools, (&tools)->philo))
        return (ft_error("wrong inputs"));
    return (0);
}