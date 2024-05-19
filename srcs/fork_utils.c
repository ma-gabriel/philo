/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/15 06:17:29 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_fork.h"

bool	take_fork(t_fork *fork)
{
	if (!pthread_mutex_lock(fork->lock))
	{
		if (fork->status == avalaible)
			fork->status = taken;
		pthread_mutex_unlock(fork->lock);
		return (true);
	}
	return (false);
}

void	release_fork(t_fork *fork)
{
	if (!pthread_mutex_lock(fork->lock))
	{
		fork->status = avalaible;
		pthread_mutex_unlock(fork->lock);
	}
}
