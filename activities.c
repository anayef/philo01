/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:20:16 by anayef            #+#    #+#             */
/*   Updated: 2023/11/25 16:01:30 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	perform_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	perform_action(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philosopher_is_eating(t_philo *philo)
{
	pick_forks(philo);
	pthread_mutex_lock(&philo->args->monitoring_mutex);
	philo->last_meal_time = get_time();
	philo->eaten_meals += 1;
	pthread_mutex_unlock(&philo->args->monitoring_mutex);
	perform_action(philo, "is eating");
	usleep(philo->args->time_to_eat * 1000);
	drop_forks(philo);
}

void	philosopher_is_sleeping(t_philo *philo)
{
	perform_action(philo, "is sleeping");
	usleep(philo->args->time_to_sleep * 1000);
}

void	*activities(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->args->nbr_of_philo == 1)
	{
		perform_action(philo, "has taken a fork");
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->args->monitoring_mutex);
		if (philo->args->simulation_should_end)
		{
			pthread_mutex_unlock(&philo->args->monitoring_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->monitoring_mutex);
		philosopher_is_eating(philo);
		philosopher_is_sleeping(philo);
		perform_action(philo, "is thinking");
	}
	return (NULL);
}
