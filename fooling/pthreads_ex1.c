#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fct(void *data)
{
	pthread_t tid;
	int thread_index = *(int *)data;

	tid = pthread_self();
	printf("Thread[%ld]: Hello Worls this is Thread [%i]\n ", tid, thread_index);
	return NULL;
}

int main(void)
{
	pthread_t thread[5];
	int i;
	int *data;
	i = 0;
	while(i < 5)
	{
		data = malloc(sizeof(int));
		*data = i;
		pthread_create(&thread[i], NULL, fct, data);
		i++;
	}
	
	i = -1;
	while(++i < 5)
		pthread_join(thread[i], NULL);
	free(data);
	return 0;
}