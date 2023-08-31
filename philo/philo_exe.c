#include "philo_info.h"

static int  thread_fork(t_philo *philo, t_box *tools)
{
    pthread_mutex_lock(&tools->fork[philo->left]);
    thread_print(philo, "has taken a fork");
    if (check_died(tools))
    {
        pthread_mutex_unlock(&tools->fork[philo->left]);
        return (1);
    }
    pthread_mutex_lock(&tools->fork[philo->right]);
    thread_print(philo, "has taken a fork");
    if (check_died(tools))
    {
        pthread_mutex_unlock(&tools->fork[philo->right]);
        pthread_mutex_unlock(&tools->fork[philo->left]);
        return (1);
    }
    return (0);
}

static int  thread_eat(t_philo *philo, t_box *tools)
{
    long    eat_start;
    long    cur_time;

    if (thread_fork(philo, tools))
        return (1);
    pthread_mutex_lock(&tools->eating_mutex);
    thread_print(philo, "is eating");
    philo->eating_num += 1;
    philo->last_eat = get_time();
    eat_start = get_time();
    while (1)
    {
        cur_time = get_time();
        if (cur_time - eat_start >= tools->time_to_eat)
            break;
        usleep(10);
    }
    pthread_mutex_unlock(&tools->eating_mutex);
    pthread_mutex_unlock(&tools->fork[philo->right]);
    pthread_mutex_unlock(&tools->fork[philo->left]);
    return (0);
}

static void    thread_sleep(t_philo *philo, t_box *tools)
{
    long    time_to_sleep;
    long    cur_time;
    long    start_sleep;

    time_to_sleep = tools->time_to_sleep;
    start_sleep = get_time();
    thread_print(philo, "is sleeping");
    while (1)
    {
        cur_time = get_time();
        if (cur_time - start_sleep >= time_to_sleep)
            break ;
        usleep(10);
    }
}

static void    *threads_action(void *arg)
{
    t_box   *tools;
    t_philo *thread;

    thread = (t_philo *)arg;
    tools = thread->tools;
    if (thread->id % 2 == 0)
        usleep(arg_usleep(tools));
    while (!check_died(tools))
    {
        if (thread_eat(thread, tools))
            break ;
        if (check_died(tools))
            break ;
        thread_sleep(thread, tools);
        if (check_died(tools))
            break ;
        thread_print(thread, "is thinking");
        usleep(10);
    }
    return (arg);
}

int philo_execute(t_box *tools, t_philo *philo)
{
    int     i;
    void    *select;

    i = 0;
    tools->init_point = get_time();
    if (tools->total_philo == 1)
    {
        thread_print(philo, "has taken a fork");
        usleep(tools->time_to_die * 1000);
        thread_print(philo, "died");
        return (0);
    }
    while (i < tools->total_philo)
    {
        philo[i].philo_begin = get_time();
        philo[i].last_eat = get_time();
        select = (void *)&(philo[i]);
        if (pthread_create(&(philo[i].thread_id), NULL, threads_action, select))
            return (1);
        i++;
    }
    philo_monitor(tools, philo);
    philo_free(tools);
    return (0);
}