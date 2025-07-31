#include "philo.h"
//./ philo 5 800 200 200 [5]

int main(int ac, char **av)
{
	t_table  table;
	if(5 == ac || 6 == ac)
	{
		parse_input(&table, av); 
		data_init(&table);
		dinner_start(&table); // Still

		//4) No leaks -> all philos are full or 1 philo is dead
		clean(&table);
		printf("heresup\n");
	}
	else
		error_exit("Wrong input\n");
	return (EXIT_SUCCESS);
}