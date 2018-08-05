#include<iostream>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include<boost/thread.hpp>

#define NUM_THREAD 4
boost::asio::io_service io,print;

bool IsPrime(int n){
	if(n<2){
		return false;
	}

	for(int i=2; i<=sqrt(n); i++){
		if(n%i==0){
			return false;
		}
	}
	return true;
}

void printfunc(int sequence, int start, int end, int count){
	printf("(%d)number of primes in %d ~ %d is %d\n",sequence,start,end,count);
}

void threadfunc(int sequence, int start, int end){
	int count=0;
	for(int i=start; i<end; i++){
		if(IsPrime(i)){
			count++;
		}
	}
	print.post(boost::bind(printfunc,sequence,start,end,count));
}

int main(void) {
	boost::thread_group threadpool;
	boost::thread_group printpool;
	boost::asio::io_service::work* work=new boost::asio::io_service::work(io);
	boost::asio::io_service::work* work2=new boost::asio::io_service::work(print);
	int range_start,range_end;
	int sequence=0;
	
	for(int i=0; i<NUM_THREAD; i++){
		threadpool.create_thread(boost::bind(&boost::asio::io_service::run,&io));
	}
	printpool.create_thread(boost::bind(&boost::asio::io_service::run,&print));


	while(1){
		scanf("%d",&range_start);
		if(range_start== -1){
			break;
		}
		scanf("%d", &range_end);
		io.post(boost::bind(threadfunc,sequence++,range_start,range_end));
	}
	delete work;
	threadpool.join_all();
	delete work2;
	printpool.join_all();

	return 0;
}
