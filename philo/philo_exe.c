#include "philo_info.h"

static int  thread_eat(t_philo *philo, t_box *tools)
{
    long    eat_start;

    pthread_mutex_lock(&tools->fork[philo->left]);
    thread_print(philo, "has taken a fork");
    pthread_mutex_lock(&tools->fork[philo->right]);
    thread_print(philo, "has taken a fork");
    pthread_mutex_lock(&tools->eating);
    thread_print(philo, "is eating");
    (philo->eat_count)++;
    philo->last_eat = get_time();
    pthread_mutex_unlock(&tools->eating);
    pthread_mutex_unlock(&tools->fork[philo->right]);
    pthread_mutex_unlock(&tools->fork[philo->left]);
    eat_start = get_time();
    while (1)
    {
        if (get_time() - eat_start >= tools->eating_time)
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

void    philo_monitor(t_box *tools, t_philo *philo)
{
    int     i;
    long    cur_time;

    while (!check_died(tools))
    {
        if (tools->eating_num != 0 && philo[i].eat_count == tools->eating_num)
        {
            change_monitor(tools);
            break ;
        }
        i = 0;
        while (i < tools->philo_num)
        {
            cur_time = get_time();
            if (cur_time - philo[i].last_eat > tools->survival_time)
            {
                thread_print(&philo[i], "died");
                change_monitor(philo->tools);
                break ;
            }
            i++;
        }
        usleep(10);
    }
}

int philo_execute(t_box *tools, t_philo *philo)
{
    int     i;
    void    *select;

    i = 0;
    tools->begin_time = get_time();
    while (i < tools->philo_num)
    {
        philo[i].begin_time = get_time();
        select = (void *)&(philo[i]);
        if (pthread_create(&(philo[i].thread_id), NULL, threads_action, select))
            return (1);
        i++;
    }
    philo_monitor(tools, philo);
    philo_free(tools);
    return (0);
}