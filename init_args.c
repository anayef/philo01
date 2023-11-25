/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:09:26 by anayef            #+#    #+#             */
/*   Updated: 2023/11/25 14:51:01 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_args *args, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	if (args)
		pthread_mutex_destroy(&args->monitoring_mutex);
	if (forks)
	{
		i = 0;
		while (i < args->nbr_of_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			// philos[i].left_fork = NULL;
			// philos[i].right_fork = NULL;
			i += 1;
		}
		free(forks);
		forks = NULL;
	}
	if (philos)
	{
		free (philos);
		philos = NULL;
	}
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i += 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i += 1;
	}
	return (res * sign);
}

int	init_args(t_args *args, char *argv[])
{
	args->nbr_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat_times = -1;
	if (argv[5])
		args->must_eat_times = ft_atoi(argv[5]);
	if (args->nbr_of_philo == 0 || args->must_eat_times == 0)
	{
		handle_error(args, NULL, NULL, "args must be greator tha 0");
		return (0);
	}
	if (pthread_mutex_init(&args->monitoring_mutex, NULL) != 0)
	{
		handle_error(args, NULL, NULL, "Failed to initialize mutex");
		return (0);
	}
	args->simulation_should_end = 0;
	return (1);
}

void	handle_error(t_args *args, pthread_mutex_t *forks,
	t_philo *philos, char *error_msg)
{
	destroy(args, forks, philos);
	printf("%s\n", error_msg);
}
