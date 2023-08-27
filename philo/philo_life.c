#include "philo_info.h"

long    get_time(void)
{
    struct  timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

int one_philo(t_box *tools)
{
    pthread_mutex_unlock(&tools->eating_mutex);
    usleep(tools->sleep_time * 2);
}

void    philo_monitor(t_box *tools, t_philo *philo)
{

}


void    philo_free(t_box *tools)
{
    int i;

    i = 0;
    while (i < tools->total_num)
        pthread_join(tools->philo[i++].thread_id, NULL);
    i = 0;
    while (i < tools->total_num)
        pthread_mutex_destroy(&tools->fork[i++]);
    free(tools->fork);
    free(tools->philo);
    pthread_mutex_destroy(&tools->write);
}