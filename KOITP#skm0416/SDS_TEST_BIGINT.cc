#include<iostream>
#include<algorithm>
using namespace std;
  
int main(){
    int T,N,plus,minus,now;
    int numbers[100000];
    long long int sum;
     
    scanf("%d",&T);
    for(int i=0; i<T; i++){
        scanf("%d %d %d",&N,&plus,&minus);
        scanf("%lld",&sum);
        for(int j=0;j<N-1;j++){
            scanf("%d",&numbers[j]);
        }
        sort(numbers,numbers+N-1);
        for(now=0; now<minus; now++){
            sum = sum - numbers[now];
        }
        for(;now<N-1;now++){
            sum = sum + numbers[now];
        }
        printf("#%d %lld\n",i+1,sum);
    }
      
   
    return 0;
}