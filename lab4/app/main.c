#include "lib.h"
#include "types.h"
#include <stdbool.h>

void producer(int id, sem_t *mutex, sem_t *full, sem_t *empty)
{
	while (true)
	{
		sem_wait(empty);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Producer %d: produce\n", id);
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(full);
		sleep(128);
	}
}

void consumer(sem_t *mutex, sem_t *full, sem_t *empty)
{
	while (true)
	{
		sem_wait(full);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Consumer: consume\n");
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(empty);
		sleep(128);
	}
}

int uEntry(void)
{
/*
	// For lab4.1
	// Test 'scanf'
    int ret = 0;
	int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	while (1)
	{
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4)
			break;
	}

	// For lab4.2
	// Test 'Semaphore'
	int i = 4;

	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 2);
	if (ret == -1)
	{
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0)
	{
		while (i != 0)
		{
			i--;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1)
	{
		while (i != 0)
		{
			i--;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		//exit();
	}

*/
	// For lab4.3
	// TODO: You need to design and test the problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
    sem_t mutex, full, empty;
	sem_init(&mutex, 1);
	sem_init(&full, 0);
	sem_init(&empty, 4);

	int id;
	for (int i = 0; i < 4; ++i)
	{
		int ret = fork();
        if (ret < 0)
        {
            printf("Fork failed when i = %d\n", i);
        }
		if (ret == 0)
		{
			id = getpid();
			producer(id-1, &mutex, &full, &empty);
		}
	}
	consumer(&mutex, &full, &empty);
    
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

	return 0;
}
