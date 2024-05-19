/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:47:44 by geymat            #+#    #+#             */
/*   Updated: 2024/05/13 21:46:23 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "meal_functions.h"

static int	is_a_number(char *num)
{
	int		i;
	ssize_t	error;

	i = 0;
	error = 0;
	while (num[i] && !error)
	{
		if (i >= 9)
			error = write(2, "please put some reasonable values\n", 34);
		if (!error && *num == '-')
			error = write(2, "I don't take negative value. "
					"Breaking time and/or space is not mandatory\n", 73);
		if (!error && \
			(num[i] == '+' || num[i] == '-' || num[i] == '*' || num[i] == '/'))
			error = write(2, "Don't expect me to calculate for you\n", 37);
		if (!error && (num[i] < '0' || num[i] > '9'))
			error = write(2, "NaN\n", 4);
		i++;
	}
	return ((int) error);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error\nwrong number of arguments buddy\n", 38);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (is_a_number(argv[i]))
			return (1);
		i++;
	}
	the_preparation(argv);
	return (0);
}
