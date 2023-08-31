/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:38:25 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/28 19:39:27 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_info.h"

void	single_free(t_box *tools)
{
	int	i;

	i = 0;
	while (i < tools->total_philo)
		pthread_mutex_destroy(&tools->fork[i++]);
	free(tools->fork);
	free(tools->philo);
	pthread_mutex_destroy(&tools->print_mutex);
	pthread_mutex_destroy(&tools->eating_mutex);
}

void	philo_free(t_box *tools)
{
	int	i;

	i = 0;
	while (i < tools->total_philo)
		pthread_join(tools->philo[i++].thread_id, NULL);
	i = 0;
	while (i < tools->total_philo)
		pthread_mutex_destroy(&tools->fork[i++]);
	free(tools->fork);
	free(tools->philo);
	pthread_mutex_destroy(&tools->print_mutex);
	pthread_mutex_destroy(&tools->eating_mutex);
}
