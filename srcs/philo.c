/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/19 22:41:10 by geymat           ###   ########.fr       */
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

void	check_death(t_table *const table, t_philo *const philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if ((now.tv_sec - philo->last_meal.tv_sec) * 1000
		+ (now.tv_usec - philo->last_meal.tv_usec) / 1000
		> table->rules->starving)
		there_is_death(table, philo->id, now);
}

void	wait_ms(int time, t_table *const table, t_philo *const philo)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&now, NULL);
	gettimeofday(&start, NULL);
	while ((now.tv_sec - start.tv_sec) * 1000000
		+ (now.tv_usec - start.tv_usec) <= ((long) time) * 1000)
	{
		check_death(table, philo);
		if (is_there_death(table))
			return ;
		gettimeofday(&now, NULL);
		usleep(3000);
	}
}

bool	eating(t_table *const table, t_philo *const philo)
{
	struct timeval	now;
	long int		timestamp;
	bool			regular;

	regular = false;
	if (!pthread_mutex_lock(&(table->mutex)))
	{
		gettimeofday(&now, NULL);
		timestamp = (now.tv_sec - table->start.tv_sec) * 1000
			+ (now.tv_usec - table->start.tv_usec) / 1000;
		if (!table->tragedy)
		{
			printf("%li %i has taken a fork\n%li %i has taken a fork\n"
				"%li %i is eating\n", timestamp, philo->id, timestamp,
				philo->id, timestamp, philo->id);
			regular = true;
		}
		pthread_mutex_unlock(&(table->mutex));
	}
	gettimeofday(&(philo->last_meal), NULL);
	wait_ms(table->rules->gobbling, table, philo);
	philo->meals++;
	release_fork(table->forks[philo->id]);
	release_fork(table->forks[(philo->id + 1) % table->rules->attendance]);
	return (regular);
}

bool	sleeping(t_table *const table, t_philo *const philo)
{
	struct timeval	now;
	long int		timestamp;
	bool			regular;

	regular = false;
	if (!pthread_mutex_lock(&(table->mutex)))
	{
		gettimeofday(&now, NULL);
		timestamp = (now.tv_sec - table->start.tv_sec) * 1000
			+ (now.tv_usec - table->start.tv_usec) / 1000;
		if (!table->tragedy)
		{
			printf("%li %i is sleeping\n", timestamp, philo->id);
			regular = true;
		}
		pthread_mutex_unlock(&(table->mutex));
	}
	wait_ms(table->rules->sleeptime, table, philo);
	return (regular);
}

bool	thinking(t_table *const table, t_philo *const philo)
{
	struct timeval	now;
	long int		timestamp;
	bool			regular;

	regular = false;
	if (!pthread_mutex_lock(&(table->mutex)))
	{
		gettimeofday(&now, NULL);
		timestamp = (now.tv_sec - table->start.tv_sec) * 1000
			+ (now.tv_usec - table->start.tv_usec) / 1000;
		if (!table->tragedy)
		{
			printf("%li %i is thinking\n", timestamp, philo->id);
			regular = true;
		}
		pthread_mutex_unlock(&(table->mutex));
	}
	return (regular);
}

bool	average_day(t_philo *const philo, t_table *const table)
{
	if (!take_fork(table->forks[philo->id]))
		return (true);
	if (!take_fork(table->forks[(philo->id + 1) % table->rules->attendance]))
	{
		release_fork(table->forks[philo->id]);
		return (true);
	}
	if (!eating(table, philo))
		return (false);
	if (!sleeping(table, philo))
		return (false);
	if (!thinking(table, philo))
		return (false);
	return (true);
}

void	*habitude(void *infos)
{
	t_philo *const	philo = ((t_philo **) infos)[0];
	t_table *const	table = ((t_table **) infos)[1];
	const int		deadline = table->rules->deadline;

	while (42)
	{
		if (deadline != -1 && deadline < philo->meals)
			return (NULL);
		if (!average_day(philo, table))
			return (NULL);
	}
	return (NULL);
}
