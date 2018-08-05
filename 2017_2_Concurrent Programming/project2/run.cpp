#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<string>
#include<deque>
#include<pthread.h>
#include<cmath>
#include<vector>

using namespace std;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t global_cond=PTHREAD_COND_INITIALIZER;
pthread_cond_t* cond;
pthread_t* threads;
deque<long>* WRlock; //readlock = tid, writelock = -tid(음수)로 표현하여 저장합니다
long N,R,E; 
long ready=0;
long job_done=0; //global execution order입니다
long long *record;
ofstream *stream;
vector<vector<long> > target;//deadlock 체킹시 사용하는 각 쓰레드가 lock한 record 목록입니다.

int DeadlockCheck(long record_id,deque<long>::iterator it,unsigned int count){
	if(count>5){//무한루프를 방지하기 위해 일정횟수 이하로만 reculsive하게 반복됩니다
		return count;
	}
	deque<long>::iterator start=WRlock[record_id].begin();
	for(;it!=start;start++){//체크를 의뢰한 lock의 앞에있는 lock들을 조사합니다
		if(abs(*start)>0){
			for(long i=0; i<3; i++){
				long next=target[abs(*start)][i];
				//lock을 건 thread가 걸어둔 다른 lock을 조사합니다
				if(next!=record_id&&next!=0){
					if(WRlock[next].empty()){
						continue;
					}
					deque<long>::iterator next_it=WRlock[next].begin();
					if(WRlock[next].end()==next_it){
						continue;
					}
					for(next_it+=1;abs(*next_it)!=abs(*start)&&next_it!=WRlock[next].end();next_it++);
					count+=DeadlockCheck(next,next_it,count+1);
					//그렇게 찾아간 lock 앞에도 lock이 존재한다면, reculsive하게 추적합니다
				}
			}
		}
	}
	return count;
}



int wakeup(long id){//lock 제거시 대기중인 lock들을 깨워줍니다
	if(WRlock[id].empty()){
		return 0;
	}
	deque<long>::iterator it=WRlock[id].begin();
	if(*it<0){//*it가 음수 = write락이므로 하나만 깨워줍니다
		pthread_cond_signal(&cond[-(*it)]);
	}
	else if(*it>0){//양수인경우 readlock이 연속으로 있으면 전부 깨워줍니다
		pthread_cond_signal(&cond[*it]);
		if(it!=WRlock[id].end()){
			for(it=it+1;it!=WRlock[id].end();it++){
				if(*it>0){
				pthread_cond_signal(&cond[*it]);
				}
				else{//writelock에 마주치면 종료합니다
					return 0;
				}
			}
		}
	}
	return 0;
}

void* Worker(void* arg){
	long long value;
	long tid =(long) arg;
	long i,j,k;
	long long a,b,result;
	int count;
	bool wait=false;
	deque<long>::iterator it;
	string filename="thread"+to_string(tid)+".txt";//commit log를 출력할 파일입니다
	stream[tid].open(filename);

	pthread_mutex_lock(&mutex);
	ready++;
	pthread_cond_wait(&global_cond,&mutex);
	pthread_mutex_unlock(&mutex);//작업을 동시에 하기 위해 대기합니다

	while(job_done<E){
		
		target[tid]={0,0,0};
		i = (rand()%R)+1;
		j = (rand()%R)+1;
		k = (rand()%R)+1;
		while(i==j||j==k||i==k){
			j = (rand()%R)+1;
			k = (rand()%R)+1;
		}//서로 다른 i,j,k를 선택합니다

		pthread_mutex_lock(&mutex);
		WRlock[i].push_back(tid);//i에 readlock을 잡습니다
		target[tid]={i,0,0};
		for(it=WRlock[i].begin();it!=WRlock[i].end();it++){
			if(*it<0){
				wait=true;
			}
		}
		if(wait==true){
			wait=false;
			if(DeadlockCheck(i,WRlock[i].end(),1)>10){//기다려야 하므로 deadlock을 체크합니다
				WRlock[i].pop_back();
				wakeup(i);
				pthread_mutex_unlock(&mutex);
				continue;//deadlock이 감지되면 undo와 continue를 합니다.
			}
			pthread_cond_wait(&cond[tid],&mutex);//deadlock이 아니면 대기합니다
		}
		pthread_mutex_unlock(&mutex);
		
		value=record[i];//i의 값을 읽습니다
		
		pthread_mutex_lock(&mutex);
		WRlock[j].push_back(-tid);//j에 writelock을 잡습니다
		target[tid]={i,j,0};
		if(WRlock[j].front()!=-tid){//맨 앞이 아니라면 대기해야 하므로 deadlock을 체크합니다
			if(DeadlockCheck(j,WRlock[j].end(),1)>10){
				for(it=WRlock[i].begin();*it!=tid;it++);
				WRlock[i].erase(it);
				wakeup(i);
				WRlock[j].pop_back();
				pthread_mutex_unlock(&mutex);
				continue;
			}
			pthread_cond_wait(&cond[tid],&mutex);
		}
		pthread_mutex_unlock(&mutex);
		
		a=record[j];
		b=value+1;
		result=a+b;
		if(a>=0&&b>=0&&result<0){//record j를 수정하기 전에 overflow를 확인합니다
			printf("Thread %ld exited by oveflow detected at record %ld\n",tid,k);
			for(it=WRlock[i].begin();*it!=tid;it++);
			WRlock[i].erase(it);
			wakeup(i);
			for(it=WRlock[j].begin();*it!=-tid;it++);
			WRlock[j].erase(it);
			wakeup(j);
			return 0;
		}
		else if(a<0&&b<0&&result>=0){
			printf("Thread %ld exited by oveflow detected at record %ld\n",tid,k);
			for(it=WRlock[i].begin();*it!=tid;it++);
			WRlock[i].erase(it);
			wakeup(i);
			for(it=WRlock[j].begin();*it!=-tid;it++);
			WRlock[j].erase(it);
			wakeup(j);
			return 0;
		}
		record[j]=result;//record j를 수정합니다

		pthread_mutex_lock(&mutex);
		WRlock[k].push_back(-tid);//record k에 writelock을 잡습니다
		target[tid]={i,j,k};
		if(WRlock[k].front()!=-tid){
			if(DeadlockCheck(k,WRlock[k].end(),1)>10){//마찬가지로 대기시 deadlock을 체크합니다
				record[j]=record[j]-value-1;
				for(it=WRlock[i].begin();*it!=tid;it++);
				WRlock[i].erase(it);
				wakeup(i);
				for(it=WRlock[j].begin();*it!=-tid;it++);
				WRlock[j].erase(it);
				wakeup(j);

				WRlock[k].pop_back();
				pthread_mutex_unlock(&mutex);
				continue;
			}
			pthread_cond_wait(&cond[tid],&mutex);
		}
		pthread_mutex_unlock(&mutex);
	
		a=record[k];
		b=-value;
		result=a+b;
		if(a>=0&&b>=0&&result<0){//overflow를 체크하고, overflow시 j의 값을 되돌립니다
			printf("Thread %ld exited by oveflow detected at record %ld\n",tid,k);
			record[j]=record[j]-value-1;
			for(it=WRlock[i].begin();*it!=tid;it++);
			WRlock[i].erase(it);
			wakeup(i);
			for(it=WRlock[j].begin();*it!=-tid;it++);
			WRlock[j].erase(it);
			wakeup(j);
			for(it=WRlock[k].begin();*it!=-tid;it++);
			WRlock[k].erase(it);
			wakeup(k);
			return 0;
		}
		else if(a<0&&b<0&&result>=0){
			printf("Thread %ld exited by oveflow detected at record %ld\n",tid,k);
			record[j]=record[j]-value-1;
			for(it=WRlock[i].begin();*it!=tid;it++);
			WRlock[i].erase(it);
			wakeup(i);
			for(it=WRlock[j].begin();*it!=-tid;it++);
			WRlock[j].erase(it);
			wakeup(j);
			for(it=WRlock[k].begin();*it!=-tid;it++);
			WRlock[k].erase(it);
			wakeup(k);
			return 0;
		}
		record[k]=result;//record k를 수정합니다

		pthread_mutex_lock(&mutex);
		for(it=WRlock[i].begin();*it!=tid;it++);
		WRlock[i].erase(it);
		for(it=WRlock[j].begin();*it!=-tid;it++);
		WRlock[j].erase(it);
		for(it=WRlock[k].begin();*it!=-tid;it++);
		WRlock[k].erase(it);//걸어뒀던 락을 제거합니다

		if(++job_done>E){//undo를 해야하는지 검사합니다
			record[j]=record[j]-value-1;
			record[k]=record[k]+value;
			wakeup(i);
			wakeup(j);
			wakeup(k);
			pthread_mutex_unlock(&mutex);
			return 0;
		}
		wakeup(i);
		wakeup(j);
		wakeup(k);
		//commit log를 출력합니다
		stream[tid]<<job_done<<" "<<i<<" "<<j<<" "<<k<<" "<<record[i]<<" "<<record[j]<<" "<<record[k]<<endl;
		pthread_mutex_unlock(&mutex);
	}
}



int main(int argc, char *argv[]){
	if(argc<4){
		printf("Please run with input arg N R E\n");
		return 0;
	}

	srand(time(NULL));
	N=atol(argv[1]);
	R=atol(argv[2]);
	E=atol(argv[3]);
	record=new long long[R+1];
	WRlock=new deque<long>[R+1];
	threads=new pthread_t[N+1];
	cond=new pthread_cond_t[N+1];
	stream=new ofstream[N+1];//필요한 변수들을 동적으로 할당합니다
	
	for(long i=1; i<N+1;i++){
		pthread_create(&threads[i],0,Worker,(void *)i);
		cond[i]=PTHREAD_COND_INITIALIZER;
	}//스레드 생성 및 conditional variable을 초기화합니다
	for(long i=0; i<N+1;i++){
		vector<long> element;
		element.resize(3);
		target.push_back(element);
	}//deadlock checking에 이용할 vector[N][3]을 생성합니다
	for(long i=1; i<R+1;i++){
		record[i]=100;
	}//record를 초기화합니다
	
	while(ready<N){
		pthread_yield();
	}//모든 스레드가 준비되면 작업을 시작합니다
	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&global_cond);
	pthread_mutex_unlock(&mutex);

	for(long i=1; i<N+1;i++){
		pthread_join(threads[i],NULL);	
	}
	for(long i=0; i<N+1;i++){
		target[i].clear();
	}//모든 작업이 완료되어 스레드가 종료되면 동적할당했던 변수들을 반환해줍니다
	target.clear();
	delete[] record;
	record=NULL;
	delete[] WRlock;
	WRlock=NULL;
	delete[] threads;
	threads=NULL;
	delete[] cond;
	cond=NULL;
	delete[] stream;
	stream=NULL;
	return 0;
}
