/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:30:39 by geymat            #+#    #+#             */
/*   Updated: 2024/05/19 22:02:34 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_philo.h"
#include "struct_table.h"
#include "struct_rules.h"

static void	*prepare_invitations(t_table *table)
{
	void	**res;
	int		i;

	res = malloc(sizeof(void *) * 2 * table->rules->attendance);
	if (!res)
		return (NULL);
	i = 0;
	while (i < table->rules->attendance)
	{
		res[i * 2] = table->philos[i];
		res[i * 2 + 1] = table;
		i++;
	}
	return (res);
}

static pthread_t	*hosting_philosophers(int attendance, void **args)
{
	pthread_t	*tids;
	int			i;

	tids = malloc(sizeof(pthread_t) * (attendance));
	if (!tids)
		return (NULL);
	i = 0;
	while (i < attendance)
	{
		pthread_create(&(tids[i]), NULL, routine, args + i * 2);
		i++;
	}
	return (tids);
}

void	end_the_meal(pthread_t *tids, int attendance)
{
	while (attendance--)
	{
		pthread_join(tids[attendance], NULL);
	}
	free(tids);
}

static bool	the_meal(t_table *table)
{
	void		*invitations;
	pthread_t	*tids;

	invitations = prepare_invitations(table);
	if (!invitations)
		return (1);
	tids = hosting_philosophers(table->rules->attendance, invitations);
	if (tids)
		end_the_meal(tids, table->rules->attendance);
	free(invitations);
	return (0);
}

bool	the_preparation(char **argv)
{
	t_rules		*rules;
	t_table		*table;
	bool		success;

	rules = create_rules(argv);
	if (!rules)
		return (1);
	table = create_table(rules);
	if (!table)
	{
		del_rules(rules);
		return (1);
	}
	success = the_meal(table);
	del_table(table);
	return (success);
}
