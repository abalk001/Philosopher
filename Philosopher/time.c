#include "philo.h"
long	get_time(t_time_code time_code)
{
	struct timeval tv;
	
	if(gettimeofday(&tv, NULL))
		error_exit("Gettime failed miserably like your life");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec/ 1e6));
	else if (MS == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (US == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("wrong input");
	return(42);
}

void	precise_unsleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MS);
	while(get_time(MS) - start < usec)
	{
		if (sim_finish(table))
			break;
		elapsed = get_time(MS) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2); 
		else
		{
			while(get_time(MS) - start < usec )	
				;
		}
	}
}