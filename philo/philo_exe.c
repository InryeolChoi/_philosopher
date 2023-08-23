#include "philo_info.h"

void    *ft_eat(void *arg)
{
    pthread_mutex_lock();
    char *str = (char *)arg;
    for (int i = 0; i < 10; i++)
        printf("%s : %d\n", str, i);
    pthread_mutex_unlock();
    return (arg);
}

void    philo_execute(t_box *tools, t_philo **philo)
{
    int i;

    i = 0;
    while (i < tools->philo_num)
        pthread_create(&philo[i++]->thread_id, NULL, ft_eat, NULL);
    i = 0;
    while (i < tools->philo_num)
        pthread_join(philo[i++]->thread_id, NULL);
}
