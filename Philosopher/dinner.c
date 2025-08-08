/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:52:39 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 20:28:48 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	precise_unsleep((philo->table->t_eat * 0.5) - philo->table->t_sleep,
		philo->table);
	if (philo->table->t_eat > philo->table->t_sleep)
		precise_unsleep(philo->table->t_eat, philo->table);
	monitoring(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	t_mtx	*first;
	t_mtx	*second;

	first = &philo->first_fork->fork;
	second = &philo->second_fork->fork;
	if (first < second)
	{
		safe_mutex_handle(&philo->first_fork->fork, LOCK);
		safe_mutex_handle(&philo->second_fork->fork, LOCK);
	}
	else
	{
		safe_mutex_handle(&philo->second_fork->fork, LOCK);
		safe_mutex_handle(&philo->first_fork->fork, LOCK);
	}
	monitoring(TAKE_FIRST_FORK, philo);
	monitoring(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MS));
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals_counters++;
	pthread_mutex_unlock(&philo->philo_mutex);
	monitoring(EATING, philo);
	precise_unsleep(philo->table->t_eat, philo->table);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
	if (philo->table->m_meals > 0
		&& philo->meals_counters == philo->table->m_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
}

static void	*long_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MS));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	monitoring(TAKE_FIRST_FORK, philo);
	while (!sim_finish(philo->table))
		usleep(300);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		philo->table->str_sim);
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	while (!sim_finish(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			return (NULL);
		if (philo->id % 2)
			precise_unsleep(2, philo->table);
		eat(philo);
		monitoring(SLEEPING, philo);
		precise_unsleep(philo->table->t_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

int	dinner_start(t_table *table)
{
	int	i;
	int	created_threads;

	created_threads = 0;
	i = -1;
	table->str_sim = get_time(MS);
	if (0 == table->m_meals)
		return (0);
	else if (1 == table->philo_nbr)
	{
		if (safe_thread_handle(&table->philos[0].thread_id,
				long_philo, &table->philos[0], CREATE))
			return (clean(table), 1);
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			if (safe_thread_handle(&table->philos[i].thread_id,
					dinner_simulation, &table->philos[i], CREATE))
			{
				table->philo_nbr = created_threads;
				return (clean(table), 1);
			}
			created_threads++;
		}
	}
	if (safe_thread_handle(&table->monitor_thread,
			monitor_dinner, table, CREATE))
	{
		table->philo_nbr = created_threads;
		return (clean(table), 1);
	}
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_sim, true);
	if (safe_thread_handle(&table->monitor_thread, NULL, NULL, JOIN))
		return (clean(table), 1);
	return (0);
}
