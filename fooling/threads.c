#include <stdio.h> // for printf
#include <stdlib.h> // for the malloc and free
#include <pthread.h> // for the threads


#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"


typedef struct s_counter
{
	pthread_mutex_t count_mutex;
	unsigned int count;
}	t_counter;

void *fct(void *data)
{
	pthread_t  tid;
	t_counter *counter;
	unsigned int i;

	tid =  pthread_self();
	counter = (t_counter *) data;

	pthread_mutex_lock(&counter->count_mutex);
	printf("[%ld]Thread :  count at thread start = %u.\n", tid, counter->count);
	pthread_mutex_unlock(&counter->count_mutex);
	
	i = -1;
	while (++i < 70000)
	{
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
	}
	
	printf("[%ld]Thread : final count = %u.\n", tid, counter->count);
	return (NULL);
}
int main(void)
{
	pthread_t tid1;
	pthread_t tid2;
	t_counter counter;
	
	counter.count = 0;
	pthread_mutex_init(&counter.count_mutex, NULL);

	printf("Main: Expected cout is %u\n", 2 * 70000);

	pthread_create(&tid1, NULL, fct, &counter);
	printf("Main: Created first thread [%ld]\n", tid1);

	pthread_create(&tid2, NULL, fct, &counter);
	printf("Main: Created second thread [%ld]\n", tid2);

	// Thread joining:
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid2);

	// Final count evaluation:
	if (counter.count != (2 * 70000))
		printf("%sMain: ERROR ! Total count is %u%s\n", RED, counter.count, NC);
	else
		printf("%sMain: OK. Total count is %u%s\n", GREEN, counter.count, NC);

	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}