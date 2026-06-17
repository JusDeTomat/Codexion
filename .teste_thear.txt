#include "header.h"

void *cont(void *arg)
{
    int nb = *(int *)arg;

    for (int i = 0; i <= nb; i++)
    {
        printf("%d\n", i);
		sleep(0.1);
    }

    return NULL;
}

int main(void)
{
	int i = 0;
    int n = 7;
	int n2 = 8;
	pthread_t th[100];

	for (int i = 0; i < 100; i++)
	{
		pthread_create(&th[i], NULL, cont, &n);
	}

	for (int i = 0; i < 100; i++)
	{
		pthread_join(th[i], NULL);
	}
    return 0;
}