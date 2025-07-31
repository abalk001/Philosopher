#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int alpha;
	pid_t pid;

	printf("Fork here \n");
	alpha = 7;
	pid = fork();
	if (pid == 0)
	{
		printf("alpha value :  %i\n ", alpha);
	}
	else if (pid > 0)
	{
		alpha = 6;
		printf("Alpha paretn value :%i\n", alpha);
	}
	return 0;
}