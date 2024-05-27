/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:03:18 by geymat            #+#    #+#             */
/*   Updated: 2024/05/27 16:38:17 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_philo.h"
#include "struct_table.h"

void	check_death(t_table *const table, t_philo *const philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if ((now.tv_sec - philo->last_meal.tv_sec) * 1000
		+ (now.tv_usec - philo->last_meal.tv_usec) / 1000
		> table->rules->starving)
		there_is_death(table, philo->id, now);
}

static void	wait_ms(int time, t_table *const table,
	t_philo *const philo)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while ((now.tv_sec - start.tv_sec) * 1000000
		+ (now.tv_usec - start.tv_usec) <= ((long) time) * 1000)
	{
		check_death(table, philo);
		if (is_there_death(table))
			return ;
		gettimeofday(&now, NULL);
		if (((long) time) * 1000 - ((now.tv_sec - start.tv_sec) * 1000000
				+ (now.tv_usec - start.tv_usec)) > 9000)
			usleep(9000);
		else if (((long) time) * 1000 - ((now.tv_sec - start.tv_sec) * 1000000
				+ (now.tv_usec - start.tv_usec)) > 0)
			usleep(((long) time) * 1000 - ((now.tv_sec - start.tv_sec)
					* 1000000 + (now.tv_usec - start.tv_usec)));
		gettimeofday(&now, NULL);
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
		philo->last_meal = now;
		timestamp = (now.tv_sec - table->start.tv_sec) * 1000
			+ (now.tv_usec - table->start.tv_usec) / 1000;
		if (!table->tragedy)
		{
			printf("%li %i is eating\n", timestamp, philo->id);
			regular = true;
		}
		pthread_mutex_unlock(&(table->mutex));
	}
	wait_ms(table->rules->gobbling, table, philo);
	philo->meals++;
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
	release_fork(table->forks[philo->id]);
	release_fork(table->forks[(philo->id + 1) % table->rules->attendance]);
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
