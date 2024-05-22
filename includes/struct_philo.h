/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:46 by geymat            #+#    #+#             */
/*   Updated: 2024/05/20 01:18:58 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_PHILO_H
# define STRUCT_PHILO_H

# include "average_header.h"
# include "struct_table.h"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	struct timeval	last_meal;
	int				meals;
}	t_philo;

t_philo	**create_philos(int attendance);
void	del_philos(t_philo **philos);

void	*behaviour(void *infos);
bool	eating(t_table *const table, t_philo *const philo);
bool	sleeping(t_table *const table, t_philo *const philo);
bool	thinking(t_table *const table, t_philo *const philo);
void	check_death(t_table *const table, t_philo *const philo);

#endif
