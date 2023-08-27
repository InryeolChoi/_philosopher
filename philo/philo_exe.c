#include "philo_info.h"

int thread_eat(t_philo *philo)
{
    int     left;
    int     right;
    t_box   *tools;

    tools = philo->tools;
    left = philo->left_fork;
    right = philo->right_fork;
    pthread_mutex_lock(&tools->fork[left]);
    thread_print(philo, "has taken a fork");
    pthread_mutex_lock(&tools->fork[right]);
    thread_print(philo, "has taken a fork");
    pthread_mutex_lock(&tools->eating);
    thread_print(philo, "is eating");
    philo->clock = get_time();
    philo->eat_count += 1;
    pthread_mutex_unlock(&tools->eating);
    pthread_mutex_unlock(&tools->fork[right]);
    pthread_mutex_unlock(&tools->fork[left]);
    return (0);
}

void    thread_sleep(t_philo *philo)
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
        thread_eat(thread);
        thread_sleep(thread);
        thread_print(thread, "is thinking");
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
        philo[i].begin_time = get_time();
        select = (void *)&(philo[i]);
        if (pthread_create(&(philo[i].thread_id), NULL, threads_action, select))
            return (1);
        i++;
    }
    philo_free(tools);
    return (0);
}