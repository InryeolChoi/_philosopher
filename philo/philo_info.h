#ifndef PHILO_INFO_H
# define PHILO_INFO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define INT_MAX 2147483647

typedef struct  s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    int             eat_count;
    long long       clock;
    struct s_box    *tools;
    pthread_t       thread_id;
}   t_philo;

typedef struct  s_box
{
    int             philo_num;
    int             survival_time;
    int             eating_time;
    int             sleep_time;
    int             eating_num;
    t_philo         *philo;
    pthread_mutex_t *fork;
    pthread_mutex_t eating;
    pthread_mutex_t write;
}   t_box;


int     ft_atoi(char *str);
int     ft_error(char *str);
void    philo_free(t_box *tools);
int     philo_input(t_box *tools, int ac, char **av);
int     philo_execute(t_box *tools, t_philo *philo);
void    thread_print(t_philo *thread, char *str);
long    get_time(void);
#endif