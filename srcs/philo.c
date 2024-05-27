/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/27 16:40:47 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_philo.h"
#include "struct_table.h"

t_philo	*create_philo(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->meals = 0;
	gettimeofday(&(philo->last_meal), NULL);
	return (philo);
}

t_philo	**create_philos(int attendance)
{
	t_philo	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(t_philo *) * (attendance + 1));
	if (!res)
		return (NULL);
	while (i < attendance)
	{
		res[i] = create_philo(i);
		if (!res[i])
		{
			del_philos(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	del_philo(t_philo *philo)
{
	free(philo);
}

void	del_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		del_philo(philos[i]);
		i++;
	}
	free(philos);
}

void	*behaviour(void *infos)
{
	t_philo *const	philo = ((t_philo **) infos)[0];
	t_table *const	table = ((t_table **) infos)[1];
	const int		deadline = table->rules->deadline;

	if (deadline)
		thinking(table, philo);
	if (philo->id % 2)
		usleep(100);
	check_death(table, philo);
	while (!(deadline != -1 && deadline <= philo->meals)
		&& !is_there_death(table))
	{
		while (!take_fork(table->forks[philo->id], philo->id, table)
			&& !is_there_death(table))
			check_death(table, philo);
		while (!take_fork(table->forks[(philo->id + 1) % \
			table->rules->attendance], philo->id, table)
			&& !is_there_death(table))
			check_death(table, philo);
		if (!eating(table, philo)
			|| !sleeping(table, philo)
			|| !thinking(table, philo))
			return (NULL);
	}
	return (NULL);
}
