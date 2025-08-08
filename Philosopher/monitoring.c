/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:10:47 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 20:29:18 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_die = philo->table->t_die;
	if (elapsed > t_die)
		return (true);
	return (false);
}

void	monitoring(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	elapsed = get_time(MS) - philo->table->str_sim;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !sim_finish(philo->table))
		printf("%-5ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !sim_finish(philo->table))
		printf("%-5ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !sim_finish(philo->table))
		printf("%-5ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !sim_finish(philo->table))
		printf("%-5ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-5ld %d died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		usleep(100);
	while (!sim_finish(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !sim_finish(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_sim, true);
				monitoring(DIED, table->philos + i);
			}
		}
		usleep(100);
	}
	return (NULL);
}
