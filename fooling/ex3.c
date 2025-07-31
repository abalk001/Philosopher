#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct shared
{
	int count;
	pthread_mutex_t mtx;
}	t_shared;


void	*fct(void *data)
{
	t_shared shared = (t_shared*)data;
	return (NULL);
}


int main(void)
{
	pthread_t threads[4];
	t_shared *data;
	int i;

	i = -1;
	while(++i < 4)
		pthread_create(&threads[i], NULL, fct, &data);
}