#include "philo.h"
#include <errno.h>
// 4/5
void	error_exit(const char *error)
{
	printf("%s\n", error); /* Recheck that */
	exit(EXIT_FAILURE);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 33);
}

bool	is_digit(char c)
{
	return ((c >= '0') && c <= '9' );
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return (ret);
}
