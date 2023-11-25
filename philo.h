/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:12:38 by anayef            #+#    #+#             */
/*   Updated: 2023/11/25 15:02:34 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args {
	int					nbr_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_times;
	pthread_mutex_t		monitoring_mutex;
	int					simulation_should_end;
}				t_args;

typedef struct s_philo {
	int					philo_nbr;
	int					eaten_meals;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	suseconds_t			last_meal_time;
	pthread_t			t_id;
	suseconds_t			start_time;
	t_args				*args;
}				t_philo;

int				create_threads(t_args *args, t_philo *philos,
					pthread_mutex_t *forks);
void			*activities(void *_philo);
void			perform_action(t_philo *philo, const char *event_id);
int				valid_args(int argc, char **argv);
int				init_args(t_args *args, char *argv[]);
suseconds_t		get_time(void);
void			handle_error(t_args *args, pthread_mutex_t *forks,
					t_philo *philos, char *error_msg);
void			destroy(t_args *args, pthread_mutex_t *forks,
					t_philo *philos);
#endif
