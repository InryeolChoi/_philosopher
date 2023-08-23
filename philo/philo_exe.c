#include "philo_info.h"

// void    *ft_eat(void *arg)
// {
//     t_box   *tools;

//     tools = (t_box *)arg;
//     pthread_mutex_lock(tools->fork);
//     for (int i = 0; i < 100; i++)
//         printf("%d ", i);
//     pthread_mutex_unlock(tools->fork);
//     return (arg);
// }

// int philo_execute(t_box *tools, t_philo **philo)
// {
//     int i;

//     i = 0;
//     tools->fork = malloc(sizeof(pthread_mutex_t) * tools->philo_num);
//     if (!tools->fork)
//         return (1);
//     pthread_mutex_init(tools->fork, NULL);
//     while (i < tools->philo_num)
//         pthread_create(&philo[i++]->thread_id, NULL, ft_eat, (void *)tools);
//     i = 0;
//     while (i < tools->philo_num)
//         pthread_join(philo[i++]->thread_id, NULL);
//     free(tools->fork);
//     return (0);
// }


int philo_execute(t_box *tools, t_philo **philo)
{
    int i;

    i = 0;
    while (i < tools->philo_num)
    {
        i++;
    }
}