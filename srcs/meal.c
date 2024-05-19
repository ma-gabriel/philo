/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:30:39 by geymat            #+#    #+#             */
/*   Updated: 2024/05/13 19:38:16 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_rules.h"
#include "struct_table.h"

int	the_preparation(char **argv)
{
	t_rules	*rules;
	t_table	*table;

	rules = create_rules(argv);
	if (!rules)
		return (1);
	table = create_table(rules);
	if (!table)
	{
		del_rules(rules);
		return (1);
	}
	return (0);
}
