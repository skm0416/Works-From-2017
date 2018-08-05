#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <pthread.h>

#define NUM_THREAD 48//동시에 몇개의 문장을 해석할 지 결정
#define NUM_GROUP 108//문장마다 동시에 몇개의 단어를 검색할 지 결정
/*즉 NUM_THREAD개의 쓰레드그륩이 각각 NUM_GROUP개의 쓰레드를 이용해 작동함*/

using namespace std;
string copied_buf[NUM_THREAD];//각 쓰레드그륩이 검색할 문장을 저장
deque<string> task_set[NUM_THREAD*NUM_GROUP];//각 쓰레드마다 검색할 단어를 저장
deque<int> output;//문제를 쓰레드그륩에 배분한 순서
multiset<pair<size_t,string>> result[NUM_THREAD];//각 쓰레드그륩의 검색 결과
pthread_t threads[NUM_THREAD*NUM_GROUP+1];// 총 쓰레드 개수, 1개는 프린트쓰레드
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//메인-프린트사이의 mutex
pthread_cond_t cond[NUM_THREAD];//각 쓰레드그륩 내부에서 이용할 mutex 및 cond
pthread_mutex_t thread_mutex[NUM_THREAD];

int job_done[NUM_THREAD*NUM_GROUP];//쓰레드의 작업상태를 확인하는 변수
int end_program=0;

void* FindingThread(void* arg){//그륩*쓰레드 수만큼 생성하여 단어를 검색함
	int tid = (long) arg;
	int thread = tid/NUM_GROUP;
	string key_word;
	size_t pos;
	size_t npos = string::npos;
	deque<string>::iterator it;
	
	/*쓰레드 생성후 wait상태로 대기*/
	if(tid==NUM_THREAD*NUM_GROUP-1){
		pthread_mutex_lock(&mutex);
		job_done[tid]=0;
		pthread_mutex_unlock(&mutex);
	}
	else{
		job_done[tid]=0;
	}
	pthread_mutex_lock(&thread_mutex[thread]);
	pthread_cond_wait(&cond[thread],&thread_mutex[thread]);
	pthread_mutex_unlock(&thread_mutex[thread]);
	
	
	while(1){
	/*쓰레드마다 할당된 task_set의 단어들을 검색*/
		for(it=task_set[tid].begin();it!=task_set[tid].end();it++){
			key_word=*it;
			pos = copied_buf[thread].find(key_word);
			if (pos != npos){
			/*단어를 찾았으면 해당하는 쓰레드그륩의 result에 추가함*/
				pthread_mutex_lock(&thread_mutex[thread]);
				result[thread].insert(make_pair(pos,key_word));
				pthread_mutex_unlock(&thread_mutex[thread]);
			}
		}
		task_set[tid].clear();
		job_done[tid]=1;//할당된 단어들을 전부 검색한 뒤 다시 wait상태로 돌입
		pthread_mutex_lock(&thread_mutex[thread]);
		pthread_cond_wait(&cond[thread],&thread_mutex[thread]);
		pthread_mutex_unlock(&thread_mutex[thread]);
	}
}

void* printThread(void* arg){//해석이 완료된 문장이 있으면 출력
	int cnt;
	int thread;
	multiset<pair<size_t, string>>::iterator result_it;
	while(1){
		while(output.empty()){//대기중인 문장이 없으면 기다리거나 종료
			if(end_program){
				return 0;
			}
			else{
				pthread_yield();
			}
		}

		pthread_mutex_lock(&mutex);
		thread=*output.begin();//다음에 출력해야할 문장을 푸는 쓰레드를 확인
		output.pop_front();
		pthread_mutex_unlock(&mutex);
		
		/*문장 해석이 완료될때까지 대기*/
		for(int i=0; i<NUM_GROUP; i++){
			while(job_done[(thread*NUM_GROUP)+i]<1){
				pthread_yield();
			}
		}

		/*검색 결과 출력*/
		result_it = result[thread].begin();
        cnt = result[thread].size();
       	if (cnt == 0){
       		cout <<"-1"<<endl;
     	}
		else{
       		for (; cnt != 0; cnt--, result_it++){
      			cout << result_it->second;
				if (cnt != 1){
					cout << "|";
           		}
       		}
			cout <<endl;
		}
		result[thread].clear();
		job_done[thread*NUM_GROUP]=-1;
	}
}

int main(){
	int N;
	int cnt;
	int thread=-1;
	set<string> word_list;
	set<string>::iterator it;
	string buf;
	char cmd;

	for(int i=0;i<NUM_THREAD;i++){//mutex 및 cond 초기화
		cond[i] = PTHREAD_COND_INITIALIZER;
		thread_mutex[i] = PTHREAD_MUTEX_INITIALIZER;
	}
	/* 프린트 쓰레드 생성*/
	pthread_create(&threads[NUM_THREAD*NUM_GROUP],0,printThread,NULL);

	for(long i=0; i<(NUM_THREAD*NUM_GROUP); i++){
		job_done[i]=-1;
		pthread_create(&threads[i],0,FindingThread,(void *)i);
	}//검색 쓰레드 생성

	/*쓰레드가 전부 준비될 때까지 대기*/
	for(int i=0; i<(NUM_THREAD*NUM_GROUP); i++){
		while(job_done[i]<0){
			pthread_yield();
		}
	}
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);


	for(int i=0;i<NUM_THREAD*NUM_GROUP;i+=NUM_GROUP){
		job_done[i]=-1;
	}
   	cin >> N;
   	for (int i = 0; i < N; i++){
       	cin >> buf;
       	word_list.insert(buf);
	}	
    
	cout << "R" << std::endl;
	while(cin>>cmd){
    	cin.get();
    	switch(cmd){
			case 'Q':
				while(thread<0){//문제를 풀 쓰레드그륩을 선택함
					for(int i=0;i<NUM_THREAD*NUM_GROUP;i+=NUM_GROUP){
						if(job_done[i]<0){
							thread=i/NUM_GROUP;
							break;
						}
					}
					pthread_yield();
				}

    			getline(cin,copied_buf[thread]);//문제 할당 및 초기화
				for(int i=0; i<NUM_GROUP; i++){
					job_done[thread*NUM_GROUP+i]=0;
				}
				cnt=0;
				for(it=word_list.begin();it!=word_list.end();it++){
					task_set[thread*NUM_GROUP+((cnt++)%NUM_GROUP)].push_back(*it);
				}//쓰레드그륩의 각 쓰레드들에 검색단어 분배

				pthread_mutex_lock(&mutex);
				output.push_back(thread);//문제 분배 순서 저장
				pthread_mutex_unlock(&mutex);
				pthread_cond_broadcast(&cond[thread]);
				thread=-1;
               	break;
           	case 'A':
    			getline(cin, buf);
               	word_list.insert(buf);
               	break;
           	case 'D':
    			getline(cin, buf);
               	word_list.erase(buf);
               	break;
       	}
   	}
	end_program=1;
	pthread_join(threads[NUM_THREAD*NUM_GROUP],NULL);
    return 0;
}

