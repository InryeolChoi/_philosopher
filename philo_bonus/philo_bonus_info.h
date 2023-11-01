/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_info.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:31:00 by inchoi            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:25 by inchoi           ###   ########.fr       */
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

typedef struct	s_box
{
	// parameter
	int			total_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			total_eat;

	// 필요한 도구
	int			*pid_box; // (malloc)
	int			philo_id; // 몇번째 철학자인지
	int			eat_count; // 철학자가 먹은 횟수
	long		init_point; // 시작 시간
	pthread_t	monitor_thread; // 모니터링 쓰레드

	// 세마포어
	sem_t	*fork;
	sem_t	*print;
	sem_t	*died;

}	t_box;

// util & input
int		ft_error(char *str);
int		ft_atoi(char *str);
long	get_time(void);

// exe & child
int 	philo_execute(t_box	*tools);
int		philo_parent(t_box *tools);
void	philo_child(t_box *tools);
void	*monitor_thread(void	*arg);

void	philo_grep_fork(t_box *tools);
void	philo_eat_food(t_box *tools);
void	philo_sleep(t_box *tools);
int		philo_print(t_box *tools, int philo_id, char *str);


#endif
