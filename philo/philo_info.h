#ifndef PHILO_INFO_H
# define PHILO_INFO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define LONG_MAX 9223372036854775807
# define LONG_MIN -9223372036854775808

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
    pthread_mutex_t *a;
    pthread_mutex_t *b;
    pthread_mutex_t *c;
    pthread_mutex_t *d;
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


int ft_atoi(char *str);
int ft_error(char *str);

#endif