/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:33:23 by anayef            #+#    #+#             */
/*   Updated: 2023/11/25 15:59:05 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	hungry(t_philo *philo)
{
	return ((get_time() - philo->last_meal_time)
		>= philo->args->time_to_die);
}

void	all_are_full(t_args *args)
{
	args->simulation_should_end = 1;
	printf("Every Philosopher had %d meals!\n", args->must_eat_times);
	pthread_mutex_unlock(&args->monitoring_mutex);
}

int	is_philo_dead(t_args *args, t_philo *philo, int *satisfied_philos)
{
	if (args->must_eat_times > 0 && philo->eaten_meals >= args->must_eat_times)
		*satisfied_philos += 1;
	if (hungry(philo))
	{
		pthread_mutex_unlock(&args->monitoring_mutex);
		perform_action(philo, "is dead");
		pthread_mutex_lock(&args->monitoring_mutex);
		args->simulation_should_end = 1;
		pthread_mutex_unlock(&args->monitoring_mutex);
		return (1);
	}
	return (0);
}

void	supervise(t_philo *philos, t_args *args)
{
	int	satisfied_philos;
	int	i;

	satisfied_philos = 0;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&args->monitoring_mutex);
		while (++i < args->nbr_of_philo)
		{
			if (is_philo_dead(args, &philos[i], &satisfied_philos))
				return ;
		}
		if (satisfied_philos == args->nbr_of_philo)
			return (all_are_full(args));
		pthread_mutex_unlock(&args->monitoring_mutex);
	}
}

int	create_threads(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philo)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL, activities,
				(void *)&philos[i]) != 0)
		{
			handle_error(args, forks, philos, "Error Creat");
			return (0);
		}
	}
	supervise(philos, args);
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		if (pthread_join(philos[i].t_id, NULL) != 0)
		{
			handle_error(args, forks, philos, "Error Joint");
			return (0);
		}
	}
	return (1);
}
