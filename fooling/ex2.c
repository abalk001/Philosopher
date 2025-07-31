#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>



void	*fct(void *data)
{
	unsigned int *counter = (unsigned int *) data;
	int i = -1;
	while(++i < 100000)
		(*counter)++;
	return(NULL);
}
int main(void)
{
	pthread_t threads[4];
	int i = -1;
	unsigned int counter;
	counter  = 0;
	while(++i < 4)
		pthread_create(&threads[i], NULL, fct, &counter);
	i = -1;
	while(++i<4)
		pthread_join(threads[i], NULL);
	printf("The finall results: %u\n", counter);
	return 0;
}