#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int array[20];
int sum = 0;


typedef struct Shared
{
	int *array;
	int total_sum;
	pthread_mutex_t mtx;
}	t_shared; 

typedef struct Data
{
	int start;
	int end;
	t_shared* shared;
}	t_Data;

pthread_mutex_t lock;
void*	fct(void* arg)
{
	t_Data* data = (t_Data*) arg;
	int local_sum = 0;
	int i = data->start - 1;

	while(++i < data->end)
		local_sum += data->shared->array[i];
	pthread_mutex_lock(&data->shared->mtx);
	data->shared->total_sum += local_sum;
	pthread_mutex_unlock(&data->shared->mtx);
	printf("Thread [%d - %d] added %d → sum now: %d\n",
       data->start, data->end - 1, local_sum, data->shared->total_sum);
	
	free(data);
	return (NULL);
}

int main(void)
{
	int i = -1;
	int* array;
	pthread_t threads[4]; //  each thread will calculate the sum of 5 numbers
	t_shared shared;

	array = malloc(sizeof(int) * 20);
	shared.array = array;
	while(++i < 20)
		array[i] = i + 1;
	shared.total_sum = 0;
	pthread_mutex_init(&shared.mtx, NULL);


	i = -1;
	while(++i < 4)
	{
		 t_Data* data = malloc(sizeof(t_Data));
		 data->start = i * 5;
		 data->end = data->start + 5;
		 data->shared = &shared;
		 pthread_create(&threads[i], NULL, fct, data);
	}

	i = -1;
	while(++i < 4)
		pthread_join(threads[i], NULL);
	printf("Total sum : %i\n", shared.total_sum);
	pthread_mutex_destroy(&shared.mtx);

	free(array);

	int ver = 0;
	i = -1;
	while(++i < 20)
		ver += i +1 ;
	printf("ver %i\n", ver);
	return (0);
}