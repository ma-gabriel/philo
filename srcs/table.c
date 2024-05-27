/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/27 15:49:59 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_table.h"

static void	del_table_except_mutex(t_table *table);

t_table	*create_table(t_rules *rules)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		del_rules(rules);
		return (NULL);
	}
	table->rules = rules;
	table->philos = create_philos(rules->attendance);
	table->forks = create_forks(rules->attendance);
	if (!table->forks || !table->philos)
	{
		del_table_except_mutex(table);
		return (NULL);
	}
	if (pthread_mutex_init(&(table->mutex), NULL) == -1)
	{
		del_table_except_mutex(table);
		return (NULL);
	}
	table->tragedy = false;
	gettimeofday(&(table->start), NULL);
	return (table);
}

static void	del_table_except_mutex(t_table *table)
{
	if (table->philos)
		del_philos(table->philos);
	if (table->rules)
		del_rules(table->rules);
	if (table->forks)
		del_forks(table->forks);
	free(table);
}

void	del_table(t_table *table)
{
	errno = EBUSY;
	while (errno == EBUSY)
	{
		errno = 0;
		pthread_mutex_destroy(&(table->mutex));
	}
	del_table_except_mutex(table);
}

void	there_is_death(t_table *table, int id, struct timeval now)
{
	if (!pthread_mutex_lock(&(table->mutex)))
	{
		if (!table->tragedy)
		{
			printf("%li %i died\n",
				(now.tv_sec - table->start.tv_sec) * 1000
				+ (now.tv_usec - table->start.tv_usec) / 1000, id + 1);
			table->tragedy = true;
		}
		pthread_mutex_unlock(&(table->mutex));
	}
}

bool	is_there_death(t_table *table)
{
	bool	res;

	res = true;
	if (!pthread_mutex_lock(&(table->mutex)))
	{
		res = table->tragedy;
		pthread_mutex_unlock(&(table->mutex));
	}
	return (res);
}
