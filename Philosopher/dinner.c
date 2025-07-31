#include "philo.h"

// ./philo 5 800 200 200 [5]


void	*long_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MS));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	monitoring(TAKE_FIRST_FORK, philo);
	while(!sim_finish(philo->table))
		usleep(200);
	return (NULL);
}

// 0) If no meals return ->0
// 1 ) if onlu one philo -> ad hoc
// 2/ Create all threads, all philos
// 2) Create a monitor thread
// 3) Sync the beggining simulation ( all start in the same time )
static void	thinking(t_philo *philo)
{
	//precise_unsleep((philo->table->t_eat * 0.5) - philo->table->t_sleep, philo->table);
	monitoring(THINKING,philo);
}
static void	eat(t_philo *philo)
{
	if (philo->id < (philo->id + 1) % philo->table->philo_nbr)
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
	philo->meals_counters++;
	monitoring(EATING, philo);
	precise_unsleep(philo->table->t_eat, philo->table);
	if (philo->table->m_meals > 0 && philo->meals_counters == philo->table->m_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	//printf("the %d ate %ld times\n", philo->id, philo->meals_counters); 
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table); // spinlock till all the philo are ready 
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MS)); // calculate the last time he ate
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr); // get the nb of threads running 
	while(!sim_finish(philo->table))
	{
		if (philo->full) // recheck this
			break;
		eat(philo);
		monitoring(SLEEPING, philo);
		precise_unsleep(philo->table->t_sleep, philo->table);
		thinking(philo);
	}
	return(NULL);
}

void dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (0 == table->m_meals)
		return; // PERFECT !!!!!!!!!
	else if (1 == table->philo_nbr)
		safe_thread_handle(&table->philos[0].thread_id, long_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);

	}
	// now all threads are ready !
	safe_thread_handle(&table->monitor_thread, monitor_dinner,table, CREATE);
	table->str_sim = get_time(MS);
	set_bool(&table->table_mutex,  &table->all_threads_ready, true);

	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_sim, true);
	safe_thread_handle(&table->monitor_thread, NULL, NULL, JOIN);

}