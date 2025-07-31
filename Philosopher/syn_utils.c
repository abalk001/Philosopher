#include "philo.h"


void	wait_all_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex,&table->all_threads_ready))
	;
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool		ret;

	ret = false;
	safe_mutex_handle(mtx, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void increase_long(t_mtx *mtx, long *value)
{
	safe_mutex_handle(mtx, LOCK);
	(*value)++;
	safe_mutex_handle(mtx, UNLOCK);
}