/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:12:22 by anayef            #+#    #+#             */
/*   Updated: 2023/11/25 15:03:42 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	perform_action(t_philo *philo, const char *event)
{
	suseconds_t	timestamp;

	pthread_mutex_lock(&philo->args->monitoring_mutex);
	if (philo->args->simulation_should_end)
	{
		pthread_mutex_unlock(&philo->args->monitoring_mutex);
		return ;
	}
	timestamp = get_time() - philo->start_time;
	printf("%d %d %s\n", timestamp, philo->philo_nbr, event);
	pthread_mutex_unlock(&philo->args->monitoring_mutex);
}
