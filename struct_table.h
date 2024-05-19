/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_table.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:46 by geymat            #+#    #+#             */
/*   Updated: 2024/05/19 22:02:14 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TABLE_H
# define STRUCT_TABLE_H

# include "average_header.h"
# include "struct_philo.h"
# include "struct_rules.h"
# include "struct_fork.h"

typedef struct s_table
{
	t_rules			*rules;
	t_fork			**forks;
	t_philo			**philos;
	pthread_mutex_t	mutex;
	bool			tragedy;
	struct timeval	start;
}	t_table;

t_table	*create_table(t_rules *rules);
void	del_table(t_table *table);

#endif
