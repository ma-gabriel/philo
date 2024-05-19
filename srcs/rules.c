/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:37 by geymat            #+#    #+#             */
/*   Updated: 2024/05/15 06:49:09 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_rules.h"

static int	ft_atoi(char *str);

t_rules	*create_rules(char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->attendance = ft_atoi(argv[1]);
	rules->starving = ft_atoi(argv[2]);
	rules->gobbling = ft_atoi(argv[3]);
	rules->sleeptime = ft_atoi(argv[4]);
	if (argv[5])
		rules->deadline = ft_atoi(argv[5]);
	else
		rules->deadline = -1;
	return (rules);
}

void	del_rules(t_rules *rules)
{
	if (rules)
		free(rules);
}

static int	ft_atoi(char *str)
{
	size_t		i;
	int			sign;
	long int	res;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	i--;
	while (str[++i] <= '9' && str[i] >= '0')
	{
		if (res * 10 + (str[i] - '0') < res)
			return (-(sign == 1));
		res = res * 10 + (str[i] - '0');
	}
	return ((int)(res * sign));
}
