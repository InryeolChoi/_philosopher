#include "philo_info.h"

static int  thread_eat(t_philo *philo, t_box *tools)
{
    long    eat_start;
    long    cur_time;

    pthread_mutex_lock(&tools->fork[philo->left]);
    thread_print(philo, "has taken a fork");
    if (tools->total_num == 1)
        return (one_philo(tools));
    pthread_mutex_lock(&tools->fork[philo->right]);
    thread_print(philo, "has taken a fork");
    pthread_mutex_lock(&tools->eating_mutex);
    thread_print(philo, "is eating");
    (philo->philo_eat)++;
    philo->last_eat = get_time();
    pthread_mutex_unlock(&tools->eating_mutex);
    pthread_mutex_unlock(&tools->fork[philo->right]);
    pthread_mutex_unlock(&tools->fork[philo->left]);
    eat_start = get_time();
    while (1)
    {
        cur_time = get_time();
        if (cur_time - eat_start >= tools->eating_time)
            break;
        usleep(10);
    }
    return (0);
}

static void    thread_sleep(t_philo *philo, t_box *tools)
{
    long    sleep_time;
    long    cur_time;
    long    start_sleep;

    sleep_time = tools->sleep_time;
    start_sleep = get_time();
    thread_print(philo, "is sleeping");
    while (1)
    {
        cur_time = get_time();
        if (cur_time - start_sleep >= sleep_time)
            break ;
        usleep(10);
    }
}

static void    *threads_action(void *arg)
{
    int     i;
    t_box   *tools;
    t_philo *thread;

    thread = (t_philo *)arg;
    tools = thread->tools;
    i = 0;
    if (thread->id % 2 == 0)
        usleep(100);
    while (1)
    {
        thread_eat(thread, tools);
        if (check_died(tools))
            break ;
        thread_sleep(thread, tools);
        if (check_died(tools))
            break ;
        thread_print(thread, "is thinking");
    }
    return (arg);
}

int philo_execute(t_box *tools, t_philo *philo)
{
    int     i;
    void    *select;

    i = 0;
    tools->init_point = get_time();
    while (i < tools->total_num)
    {
        philo[i].philo_begin = get_time();
        select = (void *)&(philo[i]);
        if (pthread_create(&(philo[i].thread_id), NULL, threads_action, select))
            return (1);
        i++;
    }
    philo_monitor(tools, philo);
    philo_free(tools);
    return (0);
}