/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rules.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:46 by geymat            #+#    #+#             */
/*   Updated: 2024/05/15 06:47:16 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_RULES_H
# define STRUCT_RULES_H

# include "average_header.h"

typedef struct s_rules
{
	int	attendance;
	int	starving;
	int	gobbling;
	int	sleeptime;
	int	deadline;
}	t_rules;

t_rules	*create_rules(char **argv);
void	del_rules(t_rules *rules);

#endif
