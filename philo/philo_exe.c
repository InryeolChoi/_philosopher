#include "philo_info.h"

int thread_eat(t_philo *philo, t_box *tools)
{
    pthread_mutex_lock();
    pthread_mutex_lock();

    pthread_mutex_unlock();
    pthread_mutex_unlock();
}

void    *threads_action(void *arg)
{
    int     i;
    t_box   *tools;
    t_philo *philo;

    philo = (t_philo *)arg;
    tools = philo->tools;
    i = 0;
    while (i < tools->philo_num)
    {
        thread_eat(philo, tools);
        thread_sleep();
        thread_think();
    }
    return (arg);
}


int philo_execute(t_box *tools, t_philo *philo)
{
    int     i;
    void    *select;

    i = 0;
    while (i < tools->philo_num)
    {
        philo[i].last_time = get_time();
        select = (void *)&(philo[i]);
        if (pthread_create(&(philo[i].thread_id), NULL, threads_action, select));
            return (-1);
        i++;
    }
    philo_free(tools);
}