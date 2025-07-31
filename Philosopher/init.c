#include "philo.h"


static void	assign_fork(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo_nbr % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->second_fork = &forks[philo_position];
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];

	}
}

static void	philo_init(t_table *table)
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
		philo->table = table; // pointing to the same table
		safe_mutex_handle(&philo->philo_mutex, INIT); 
		assign_fork(philo, table->fork, i); // we assigne forks here
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr); // we allocate an "array" of N philo
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_nbr); // We allocate an "array" of N mutex 
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i;
	}
	philo_init(table);
}
