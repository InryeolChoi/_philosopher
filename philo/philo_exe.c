#include "philo_info.h"

int thread_eat(t_philo *philo, t_box *tools)
{
    pthread_mutex_lock(philo->left_fork);
    thread_print(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    thread_print(philo, "has taken a fork");
    thread_print(philo, "is eating");
    philo->clock = get_time();
    philo->eat_count += 1;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (0);
}

int thread_sleep(t_philo *philo, t_box *tools)
{
    thread_print(philo, "is sleeping");
    philo->clock = get_time();
}

void    *threads_action(void *arg)
{
    int     i;
    t_box   *tools;
    t_philo *thread;

    thread = (t_philo *)arg;
    tools = thread->tools;
    i = 0;
    if (thread->id % 2 == 0)
        usleep(100);
    while (i < tools->philo_num)
    {
        thread_eat(thread, tools);
        thread_sleep(thread, tools);
        thread_think(thread, tools);
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
        philo[i].clock = get_time();
        select = (void *)&(philo[i]);
        if (pthread_create(&(philo[i].thread_id), NULL, threads_action, select));
            return (-1);
        i++;
    }
    philo_free(tools);
}