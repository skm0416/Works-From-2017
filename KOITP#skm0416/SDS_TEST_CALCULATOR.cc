#include<iostream>
#include<set>
using namespace std;
  
  
int main(){
    multiset<long long int> numbers;
    multiset<long long int>::iterator target; 
    long long int sum;
    long long int value;
    int T,N,temp;
      
    scanf("%d",&T);
    for(int i=0; i<T; i++){
        sum = 0;
        scanf("%d",&N);
        for(int j=0; j<N; j++){
            scanf("%d",&temp);
            numbers.insert(temp);
        }
        for(int k=0; k<(N-1); k++){
            target = numbers.begin();
            value = *target + (*++target);
            sum += value;
            numbers.erase(numbers.begin(),++target);
            numbers.insert(value);
        }
        numbers.clear();
        printf("#%d %lld\n",i+1,sum);
    }
      
    return 0;
}