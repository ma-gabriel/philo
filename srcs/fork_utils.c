/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/22 23:47:08 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_fork.h"
#include "struct_table.h"

static void	announce_fork_taken(int id, t_table *table)
{
	struct timeval	now;

	if (!pthread_mutex_lock(&(table->mutex)))
	{
		gettimeofday(&now, NULL);
		if (!table->tragedy)
			printf("%li %i has taken a fork\n", (now.tv_sec - table->start.tv_sec) * 1000
					+ (now.tv_usec - table->start.tv_usec) / 1000, id);
	}
	pthread_mutex_unlock(&(table->mutex));
}

bool	take_fork(t_fork *fork, int id, t_table *table)
{
	bool	res;

	res = false;
	if (!pthread_mutex_lock(&(fork->lock)))
	{
		if (fork->status == avalaible)
		{
			res = true;
			announce_fork_taken(id, table);
			fork->status = taken;
		}
		pthread_mutex_unlock(&(fork->lock));
		return (res);
	}
	return (false);
}

void	release_fork(t_fork *fork)
{
	if (!pthread_mutex_lock(&(fork->lock)))
	{
		fork->status = avalaible;
		pthread_mutex_unlock(&(fork->lock));
	}
}
