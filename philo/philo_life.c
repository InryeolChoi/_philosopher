#include "philo_info.h"

static void    multiple_lock(t_box *tools)
{
    pthread_mutex_lock(&tools->eating_mutex);
    pthread_mutex_lock(&tools->flag_mutex);
}

static void    multiple_unlock(t_box *tools)
{
    pthread_mutex_unlock(&tools->flag_mutex);
    pthread_mutex_unlock(&tools->eating_mutex);
}

static void print_died(t_box *tools, t_philo *philo, int died)
{
    pthread_mutex_lock(&tools->flag_mutex);
    if (tools->died_flag)
        thread_print(&philo[died], "died");
    pthread_mutex_unlock(&tools->flag_mutex);
}

void    philo_monitor(t_box *tools, t_philo *philo)
{
    int i;
    int died;

    died = -1;
    while (1)
    {
        i = -1;
        while (++i < tools->total_philo)
        {
            multiple_lock(tools);
            if ((philo[i].eating_num >= tools->total_eat) || \
                (get_time() - philo[i].last_eat >= tools->time_to_die))
            {
                tools->died_flag = 1;
                multiple_unlock(tools);
                died = i;
                break;
            }
            multiple_unlock(tools);
        }
        if (died != -1)
            break ;
    }
    print_died(tools, philo, died);
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