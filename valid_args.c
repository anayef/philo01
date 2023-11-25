/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:58:32 by anayef            #+#    #+#             */
/*   Updated: 2023/11/19 22:39:22 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_all_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]))
				return (0);
			j ++;
		}
		i ++;
	}
	return (1);
}

int	valid_args(int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || !is_all_digits(argv))
	{
		handle_error(NULL, NULL, NULL, "invalid args");
		return (0);
	}
	return (1);
}
