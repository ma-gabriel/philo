/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:46 by geymat            #+#    #+#             */
/*   Updated: 2024/05/15 08:19:40 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_PHILO_H
# define STRUCT_PHILO_H

# include "average_header.h"

typedef struct s_philo
{
	int				id;
	struct timeval	last_meal;
	int				meals;
}	t_philo;

t_philo	**create_philos(int attendance);
void	del_philos(t_philo **philos);

#endif
