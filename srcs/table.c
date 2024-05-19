/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/19 21:38:35 by geymat           ###   ########.fr       */
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
	table->forks = create_forks(rules->attendance);
	if (!table->forks || !table->philos)
	{
		del_table(table);
		return (NULL);
	}
	if (pthread_mutex_init(&(table->mutex), NULL) == -1)
	{
		del_table(table);
		return (NULL);
	}
	table->tragedy = false;
	gettimeofday(&(table->start), NULL);
	return (table);
}

void	del_table(t_table *table)
{
	if (table->philos)
		del_philos(table->philos);
	if (table->rules)
		del_rules(table->rules);
	if (table->forks)
		del_forks(table->forks);
	errno = EBUSY;
	while (errno == EBUSY)
	{
		errno = 0;
		pthread_mutex_destroy(&(table->mutex));
	}
	free(table);
}
