#include "philo_info.h"

int check_died(t_box *tools)
{
    if (tools->died_flag == 1)
        return (1);
    return (0);
}

void    philo_monitor(t_box *tools, t_philo *philo)
{
    int i;
    int died;

    i = 0;
    died = 0;
    while (!(tools->died_flag))
    {
        i = 0;
        while (i < tools->total_philo)
        {
            if (philo[i].eating_num >= tools->total_eat)
                tools->died_flag = 1;
            else if (philo[i].last_eat >= tools->time_to_die)
                tools->died_flag = 1;
            died = i;
            i++;
        }
    }
    if (tools->died_flag)
        thread_print(&philo[died], "died");
}

void    philo_free(t_box *tools)
{
    int i;

    i = 0;
    while (i < tools->total_philo)
        pthread_join(tools->philo[i++].thread_id, NULL);
    i = 0;
    while (i < tools->total_philo)
        pthread_mutex_destroy(&tools->fork[i++]);
    free(tools->fork);
    free(tools->philo);
    pthread_mutex_destroy(&tools->print_mutex);
    pthread_mutex_destroy(&tools->eating_mutex);
}