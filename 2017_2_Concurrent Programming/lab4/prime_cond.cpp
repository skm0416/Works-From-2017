#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREAD  10

int thread_ret[NUM_THREAD];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t threads[NUM_THREAD];

int job_done;
int range_start;
int range_end;
int ready=0;

bool IsPrime(int n) {
    if (n < 2) {
        return false;
    }

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void* ThreadFunc(void* arg) {
    long tid = (long)arg;
    pthread_mutex_lock(&mutex);
    ready++;
    pthread_cond_wait(&cond,&mutex);
    pthread_mutex_unlock(&mutex);
    
    while(1){
   	 // Split range for this thread
   	 int start = range_start + ((range_end - range_start) / NUM_THREAD) * tid;
   	 int end = range_start + ((range_end - range_start) / NUM_THREAD) * (tid+1);
   	 if (tid == NUM_THREAD - 1) {
    	   	 end = range_end + 1;
   	 }
    
   	 long cnt_prime = 0;
     	 for (int i = start; i < end; i++) {
       		 if (IsPrime(i)) {
         	   cnt_prime++;
        	}
    	}
    	thread_ret[tid] = cnt_prime;
        pthread_mutex_lock(&mutex);
	job_done++;
    	pthread_cond_wait(&cond,&mutex);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void) {
    // Create threads to work
    for (long i = 0; i < NUM_THREAD; i++) {
        if (pthread_create(&threads[i], 0, ThreadFunc, (void*)i) < 0) { 
            printf("pthread_create error!\n");
            return 0;
        }
    }
    while(ready<NUM_THREAD){
	pthread_yield();
    }
    while (1) {
        // Input range
        scanf("%d", &range_start);
        if (range_start == -1) {
        	break;
	}
        scanf("%d", &range_end);

    	job_done=0;
	pthread_mutex_lock(&mutex);
    	pthread_cond_broadcast(&cond);
   	pthread_mutex_unlock(&mutex);
	
	while(job_done<NUM_THREAD){
		pthread_yield();
	}
        // Collect results
        int cnt_prime = 0;
        for (int i = 0; i < NUM_THREAD; i++) {
            cnt_prime += thread_ret[i];
        }
        printf("number of prime: %d\n", cnt_prime);
    }
 
    return 0;
}

