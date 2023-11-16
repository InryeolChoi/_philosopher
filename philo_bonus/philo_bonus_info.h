/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_info.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:31:00 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/08 19:52:47 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_INFO_H
# define PHILO_BONUS_INFO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define INT_MAX 2147483647

typedef struct s_box
{
	int			total_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			total_eat;
	int			*pid_box;
	int			philo_id;
	int			eat_count;
	long		init_point;
	long		last_eat;
	pthread_t	monitor_thread;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*died;
	sem_t		*lasteat_sem;
	sem_t		*eatcnt_sem;
	char		*semname_died;
	char		*semname_lasteat;
	char		*semname_eatcnt;
}	t_box;

// util & input
int		ft_error(char *str);
int		ft_atoi(char *str);
char	*ft_itoa(int n);
long	get_time(void);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);

// exe & child
int		philo_execute(t_box	*tools);
int		philo_single(t_box *tools);
void	philo_child(t_box *tools);
void	*monitor_thread(void *arg);
void	monitor_thread_time(t_box *tools);
void	monitor_thread_eatcnt(t_box *tools);
int		philo_parent(t_box *tools);
int		philo_kill(t_box *tools, int exit_code);
int		philo_free(t_box *tools);
void	philo_grep_fork(t_box *tools);
void	philo_eat_food(t_box *tools);
void	philo_sleep(t_box *tools);
int		philo_print(t_box *tools, int philo_id, char *str);

#endif
