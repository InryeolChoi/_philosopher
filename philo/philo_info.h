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
    int             id;             // 철학자 id
    int             eating_num;     // 철학자의 식사 횟수
    int             left;           // 왼쪽 포크
    int             right;          // 오른쪽 포크
    long            philo_begin;    // 철학자의 활동 시작 시간
    long            last_eat;       // 철학자의 최근 식사 시간
    struct s_box    *tools;         // 도구
    pthread_t       thread_id;      // 쓰레드 id
}   t_philo;

typedef struct  s_box
{
    t_philo         *philo;
    int             total_philo;    // 철학자 수, av[1]
    int             time_to_die;    // time to die, av[2]
    int             time_to_eat;    // time to eat, av[3]
    int             time_to_sleep;  // time to sleep, av[4]
    int             total_eat;      // 식사 횟수, av[5]
    long            init_point;     // 프로그램 시작 시간
    int             died_flag;      // 종료 플래그
    pthread_mutex_t *fork;          // 뮤택스 : 포크
    pthread_mutex_t eating_mutex;   // 뮤택스 : 먹기
    pthread_mutex_t print_mutex;    // 뮤택스 : 프린트
    pthread_mutex_t flag_mutex;     // 뮤택스 : 사망여부
}   t_box;

int     ft_atoi(char *str);
int     ft_error(char *str);
long    get_time(void);
void    thread_print(t_philo *thread, char *str);
int     philo_input(t_box *tools, int ac, char **av);
int     philo_execute(t_box *tools, t_philo *philo);
int     check_died(t_box *tools);
void    philo_monitor(t_box *tools, t_philo *philo);
void    philo_free(t_box *tools);


#endif