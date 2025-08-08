/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:08:02 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 20:31:02 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo_nbr % 2 == 0)
	{
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->first_fork = &forks[philo_position];
	}
	else
	{
		philo->second_fork = &forks[philo_position];
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counters = 0;
		philo->table = table;
		if (safe_mutex_handle(&philo->philo_mutex, INIT))
		{
			while (--i >= 0)
				safe_mutex_handle(&table->philos[i].philo_mutex, DESTROY);
			return (EXIT_FAILURE);
		}
		assign_fork(philo, table->fork, i);
	}
	return (EXIT_SUCCESS);
}

static int	normas_abibas(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (safe_mutex_handle(&table->fork[i].fork, INIT))
		{
			while (--i >= 0)
				safe_mutex_handle(&table->fork[i].fork, DESTROY);
			safe_mutex_handle(&table->table_mutex, DESTROY);
			safe_mutex_handle(&table->write_mutex, DESTROY);
			free(table->fork);
			free(table->philos);
			return (EXIT_FAILURE);
		}
		table->fork[i].fork_id = i;
	}
	return (EXIT_SUCCESS);
}

int	data_init(t_table *table)
{
	table->end_sim = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	if (safe_mutex_handle(&table->table_mutex, INIT))
	{	
		safe_mutex_handle(&table->table_mutex, DESTROY);
		return (EXIT_FAILURE);
	}
	if (safe_mutex_handle(&table->write_mutex, INIT))
	{
		safe_mutex_handle(&table->table_mutex, DESTROY);
		safe_mutex_handle(&table->write_mutex, DESTROY);
		return (EXIT_FAILURE);
	}
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos)
	{
		safe_mutex_handle(&table->table_mutex, DESTROY);
		safe_mutex_handle(&table->write_mutex, DESTROY);
		return (EXIT_FAILURE);
	}
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->fork)
	{
		safe_mutex_handle(&table->table_mutex, DESTROY);
		safe_mutex_handle(&table->write_mutex, DESTROY);
		free(table->philos);
		return (EXIT_FAILURE);
	}
	if (normas_abibas(table))
		return (EXIT_FAILURE);
	return (philo_init(table));
}
