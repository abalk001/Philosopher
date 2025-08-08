/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:30:46 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 17:46:31 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettime failed miserably like your life");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MS == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (US == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("wrong input");
	return (69);
}

void	precise_unsleep(long t_to_task, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MS);
	while (get_time(MS) - start < t_to_task)
	{
		if (sim_finish(table))
			break ;
		elapsed = get_time(MS) - start;
		rem = t_to_task - elapsed;
		if (rem > 500)
			usleep(rem - 200);
		else
			usleep(100);
	}
}

//200 800 200 200
// 4 410 200 200
// 4 410 200 200 10