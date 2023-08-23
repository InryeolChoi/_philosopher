#ifndef PHILO_INFO_H
# define PHILO_INFO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define INT_MAX 2147483647

typedef struct  s_box
{
    int             philo_num;
    int             survival_time;
    int             eating_time;
    int             sleep_time;
    int             eating_num;
    int             finish;
    int             flag;
    pthread_mutex_t *fork;
    pthread_mutex_t *print;
    pthread_mutex_t *monitor;
    pthread_mutex_t *eat_times;
    pthread_mutex_t *last_eat;
}   t_box;

typedef struct  s_philo
{
    int         id;
    int         eat_count;
    int         left;
    int         right;
    long        last_eat;
    long        last_time;
    t_box       *tools;
    pthread_t   thread_id;
}   t_philo;


int     ft_atoi(char *str);
int     ft_error(char *str);
void    *fail_alloc_philo(t_philo **philo, int num);
void    philo_execute(t_box *tools, t_philo **philo);
void    philo_free(t_box *tools, t_philo **philo);

#endif