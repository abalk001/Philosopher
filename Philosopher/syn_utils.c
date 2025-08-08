/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:30:21 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 20:29:07 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mtx, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	increase_long(t_mtx *mtx, long *value)
{
	safe_mutex_handle(mtx, LOCK);
	(*value)++;
	safe_mutex_handle(mtx, UNLOCK);
}
