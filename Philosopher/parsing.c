#include "philo.h"


// /philo av[1] ..... av[5]
// no max reached and timestamps > 60ms (1s)

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*nbr;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("check input");
	if (!is_digit(*str))
		error_exit("check_input");
	nbr = str; // the actual nbr
	while (is_digit(*str++))
		++len;
	if (len > 10) // recheck that 
		error_exit("too long man");
	return (nbr);
}

static long	ft_atoi(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str); // check if it's a number ot not 
	while (is_digit(*str))
		num = (num * 10) + ( *str++ - 48);
	if (num > INT_MAX)
		error_exit("too big");
	return (num);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	printf("%li\n", table->philo_nbr);
	table->t_die = ft_atoi(av[2]); 
	table->t_eat = ft_atoi(av[3]);
	table->t_sleep = ft_atoi(av[4]);
	if (av[5])
		table->m_meals = ft_atoi(av[5]);
	else
		table->m_meals = -1;
}
