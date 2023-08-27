#include "philo_info.h"

long    get_time(void)
{
    struct  timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

int check_died(t_box *tools)
{
    pthread_mutex_lock(&tools->monitor_check);
    if (tools->monitor == 1)
    {
        pthread_mutex_unlock(&tools->monitor_check);
        return (1);
    }
    else
    {
        pthread_mutex_unlock(&tools->monitor_check);
        return (0);
    }
}

void    change_monitor(t_box *tools)
{
    pthread_mutex_lock(&tools->monitor_mutex);
    if (tools->monitor == 0)
        tools->monitor = 1;
    pthread_mutex_unlock(&tools->monitor_mutex);
}