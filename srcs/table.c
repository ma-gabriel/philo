/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/15 07:23:23 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_table.h"

t_table	*create_table(t_rules *rules)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->rules = rules;
	table->philos = create_philos(rules->attendance);
	if (!table->philos)
	{
		del_table(table);
		return (NULL);
	}
	return (table);
}

void	del_table(t_table *table)
{
	if (table->philos)
		del_philos(table->philos);
	if (table->forks)
		del_forks(table->forks);
	free(table);
}
