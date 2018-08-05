#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

#define NUMBER_OF_PHIL 5
#define EXEC_TIME 60

enum PHIL_STATE
{
	HUNGRY = 0,
	EATING = 1,
	THINKING = 2
};

typedef struct philosopher
{
	unsigned short num_eat;
	enum PHIL_STATE state;
} philosopher;

philosopher phil[NUMBER_OF_PHIL];
sem_t chopstick[NUMBER_OF_PHIL];
int phil_number=0;

void idlewait()
{
	int sleepTimeMS = (rand() %91 + 10);
	usleep(sleepTimeMS*1000);
}


unsigned int tick()
{
	struct timeval tv;
	gettimeofday(&tv, (void *)0);
	return tv.tv_sec *(unsigned int)1000 + tv.tv_usec / 1000;
}

void initPhil(void)
{
	int i;
	for(i=0; i<NUMBER_OF_PHIL;i++)
	{
		phil[i].num_eat=0;
		phil[i].state = THINKING;
		sem_init(&chopstick[i],0,1);
	}
}

void* dining(void *arg)
{
	int t=EXEC_TIME;
	int i=phil_number++;
	int status=0;
	unsigned int start_time=tick();

	while(t>0)
	{
		if(phil[i].state==THINKING)
		{
			printf("phil[%d] THINKING\n",i);
			idlewait();
			phil[i].state=HUNGRY;
		}
		else if(phil[i].state==EATING)
		{
			printf("phil[%d] EATING\n",i);
			idlewait();
			sem_post(&chopstick[i]);
			sem_post(&chopstick[(i+1)%NUMBER_OF_PHIL]);
			phil[i].num_eat++;
			phil[i].state=THINKING;
		}
		else if(phil[i].state==HUNGRY)
		{	
			if(status==0)
			{
				printf("phil[%d] HUNGRY\n",i);
				status=1;
			}
			if(i%2==0)
			{
				sem_wait(&chopstick[i]);
				if(sem_trywait(&chopstick[(i+1)%NUMBER_OF_PHIL])==-1)					
				{
					sem_post(&chopstick[i]);
				}	
				else
				{
					phil[i].state=EATING;
					status=0;
				}
			}
			else
			{
				sem_wait(&chopstick[(i+1)%NUMBER_OF_PHIL]);
				if(sem_trywait(&chopstick[i])==-1)
				{
					sem_post(&chopstick[(i+1)%NUMBER_OF_PHIL]);
				}					
				else
				{
					phil[i].state=EATING;
					status=0;
				}
			}
			
		}
		t= EXEC_TIME-(tick()/1000 - start_time/1000);
	}
}	

int main(void)
{
	pthread_t t[NUMBER_OF_PHIL];
	unsigned short i, args[NUMBER_OF_PHIL], minCount = USHRT_MAX, maxCount=0;
	long long start=0, end=0;
	void* thread_result;
	srand(time(NULL));
	
	initPhil();
	start = tick();
	
	for(i=0; i<NUMBER_OF_PHIL;i++)
	{
		pthread_create(&t[i],NULL, dining,(void *)args[i]);
	}
	for(i=0; i<NUMBER_OF_PHIL;i++)
	{
		pthread_join(t[i], NULL);
	}
	for(i=0; i<NUMBER_OF_PHIL;i++)
	{
		sem_destroy(&chopstick[i]);
	}

	end=tick();
	
	printf("\n\n");
	for(i=0;i<NUMBER_OF_PHIL;i++)
	{
		printf("Philosopher %d eating count : %d\n\n", i, phil[i].num_eat);
	}
	printf("Total Exec Time : %lld.%lld sec\n\n", (end-start)/1000, (end-start)%1000);
	return 0;
}
