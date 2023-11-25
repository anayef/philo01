/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:32:32 by anayef            #+#    #+#             */
/*   Updated: 2023/11/25 15:03:13 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(pthread_mutex_t *forks, int until)
{
	int	i;

	i = 0;
	while (i <= until)
	{
		pthread_mutex_destroy(&forks[i]);
		i += 1;
	}
	free(forks);
}

pthread_mutex_t	*init_forks(t_args *args)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(args->nbr_of_philo * sizeof(pthread_mutex_t));
	if (!forks)
		handle_error(args, NULL, NULL, "Error Allocating Memory");
	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_forks(forks, i);
			handle_error(args, NULL, NULL, "failed to initialize mutex");
		}
		i += 1;
	}
	return (forks);
}

t_philo	*init_philos(t_args *args, pthread_mutex_t *forks_array)
{
	t_philo	*philos;
	int		i;

	philos = malloc(args->nbr_of_philo * sizeof(t_philo));
	if (!philos)
		handle_error(args, forks_array, NULL, "Error Allocating Memory");
	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].philo_nbr = i + 1;
		philos[i].eaten_meals = 0;
		philos[i].left_fork = &forks_array[i];
		philos[i].right_fork = &forks_array[(i + 1) % args->nbr_of_philo];
		philos[i].last_meal_time = get_time();
		philos[i].args = args;
		i += 1;
	}
	return (philos);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	if (!valid_args(argc, argv) || !init_args(&args, argv))
		return (EXIT_FAILURE);
	forks = init_forks(&args);
	philos = init_philos(&args, forks);
	if (!create_threads(&args, philos, forks))
		return (EXIT_FAILURE);
	destroy(&args, forks, philos);
	return (0);
}
