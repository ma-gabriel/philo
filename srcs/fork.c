/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/19 18:38:17 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_fork.h"

static void		del_fork(t_fork *fork);
static t_fork	*create_fork(void);

static t_fork	*create_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(&(fork->lock), NULL) == -1)
	{
		free(fork);
		return (NULL);
	}
	fork->status = avalaible;
	return (fork);
}

t_fork	**create_forks(int attendance)
{
	t_fork	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(t_fork *) * (attendance + 1));
	if (!res)
		return (NULL);
	while (i < attendance)
	{
		res[i] = create_fork();
		if (!res[i])
		{
			del_forks(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	del_forks(t_fork **forks)
{
	int	i;

	i = 0;
	while (forks[i])
	{
		del_fork(forks[i]);
		i++;
	}
	free(forks);
}

static void	del_fork(t_fork *fork)
{
	errno = EBUSY;
	while (errno == EBUSY)
	{
		errno = 0;
		pthread_mutex_destroy(&(fork->lock));
	}
	free(fork);
}
