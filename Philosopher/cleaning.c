#include "philo.h"

void	clean(t_table *table)
{
	t_philo *philo;
	int	i;

	i = -1;
	while(++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->fork);
	free(table->philos);
}