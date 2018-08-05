#include<stdio.h>
#include<pthread.h>

#define NUM_THREAD 8
#define NUM_WORK 1000000

int cnt_global;
int tail=-1;
bool regs[NUM_THREAD*NUM_WORK];

void* Work(void* args){
	int tid =(long) args;
	int tmp;
	int regnum;
	for (int i=0; i<NUM_WORK; i++) {
		regnum=i+tid*NUM_WORK;
		tmp=__sync_lock_test_and_set(&tail,regnum);
		if(tmp==-1){
			cnt_global++;
			regs[regnum]=false;
		}
		else{
			while(regs[tmp]==true){
				pthread_yield();
			}
			cnt_global++;
			regs[tmp]=true;
			regs[regnum]=false;
		}
	}
}

int main(void){
	pthread_t threads[NUM_THREAD];
	
	for(long i=0; i<NUM_THREAD*NUM_WORK;i++){
		regs[i]=true;
	}
	for(long i=0; i<NUM_THREAD; i++){
		pthread_create(&threads[i], 0, Work, (void *)i);
	}
	for(int i=0; i<NUM_THREAD; i++){
		pthread_join(threads[i],0);
	}
	printf("cnt_global: %d\n", cnt_global);
}
