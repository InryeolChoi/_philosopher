/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_info.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:55:50 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/28 19:57:03 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INFO_H
# define PHILO_INFO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define LOCK 0
# define UNLOCK 1

typedef struct s_philo
{
	int				id;
	int				eating_num;
	int				left;
	int				right;
	long			philo_begin;
	long			last_eat;
	struct s_box	*tools;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_box
{
	t_philo			*philo;
	int				total_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_eat;
	long			init_point;
	int				died_flag;
	int				*fork;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	died_flag_mutex;
	pthread_mutex_t	start_mutex;
}	t_box;

int		ft_atoi(char *str);
long	get_time(void);
int		arg_usleep(t_box *tools);
int		philo_input(t_box *tools, int ac, char **av);
int		philo_single(t_box *tools, t_philo *philo);
int		philo_execute(t_box *tools, t_philo *philo);
int		philo_print(t_philo *thread, char *str);
void	philo_monitor(t_box *tools, t_philo *philo);
int		philo_check(t_box *tools);
void	philo_free(t_box *tools);

#endif
