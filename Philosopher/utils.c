/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:30:54 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 17:44:35 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(const char *error)
{
	printf("%s\n", error);
	return (EXIT_FAILURE);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 33);
}

bool	is_digit(char c)
{
	return ((c >= '0') && c <= '9' );
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return (ret);
}
