/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fork.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:46 by geymat            #+#    #+#             */
/*   Updated: 2024/05/15 07:08:32 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_FORK_H
# define STRUCT_FORK_H

# include "average_header.h"

enum e_status
{
	avalaible,
	taken
};

typedef struct s_fork
{
	pthread_mutex_t	*lock;
	enum e_status	status;
}	t_fork;

t_fork	**create_forks(int attendance);
void	del_forks(t_fork **forks);

bool	take_fork(t_fork *fork);
void	release_fork(t_fork *fork);

#endif
