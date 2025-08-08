/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:21:57 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 17:43:24 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_input(const char *str)
{
	int	len;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (error_exit("check input"));
	if (!is_digit(*str))
		return (error_exit("check input"));
	while (is_digit(*str++))
		++len;
	if (len > 10)
		return (error_exit("check input"));
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_table	table;

	i = 0;
	if (5 == ac || 6 == ac)
	{
		while (++i < ac)
		{
			if (valid_input(av[i]))
				return (1);
		}
		parse_input(&table, av);
		if (data_init(&table))
			return (1);
		if (dinner_start(&table))
			return (1);
		clean(&table);
	}
	else
		error_exit("Wrong input\n");
	return (EXIT_SUCCESS);
}
