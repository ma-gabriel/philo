/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/15 08:59:15 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_philo.h"
#include "struct_table.h"

t_philo	*create_philo(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_fork));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->meals = 0;
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

static bool	try_taking_fork(t_fork *fork, t_philo *philo, struct timeval start)
{
	struct timeval	now;

	if (take_fork(fork) == false)
		return (false);
	gettimeofday(&now, NULL);
	printf("%li %i has taken a fork\n", (now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec) / 1000, philo->id);
	return (true);
}

void	average_day(t_philo *const philo, t_table *const table, bool *const death)
{
	struct timeval	now;

	if (try_taking_fork(table->forks[philo->id], philo, table->start) == false)
		return ;
	if (try_taking_fork(table->forks[(philo->id + 1) % table->rules->attendance], philo, table->start) == false)
	{
		release_fork(table->forks[philo->id]);
		return ;
	}
	gettimeofday(&(philo->last_meal), NULL);
	usleep(((long) table->rules->gobbling) * 1000);
	release_fork(table->forks[philo->id]);
	release_fork(table->forks[(philo->id + 1) % table->rules->attendance]);
	philo->meals++;
	usleep(((long) table->rules->sleeptime) * 1000);
	gettimeofday(&now, NULL);
	if ((now.tv_sec - table->start.tv_sec) * 1000 + (now.tv_usec - table->start.tv_usec) / 1000 > table->rules->starving)
		*death = 1;
}

void	habitude(void **infos)
{
	t_philo *const	philo = infos[0];
	t_table *const	table = infos[1];
	bool *const		death = infos[2];

	while (42)
	{
		if (table->rules->deadline != -1 && table->rules->deadline < philo->meals)
			exit(0);
		if (*death == true)
			exit(1);
		average_day(philo, table, death);
	}
}
