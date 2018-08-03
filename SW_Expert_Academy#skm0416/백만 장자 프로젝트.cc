#include<stdio.h>
int value_array[1000000];

int main(){
    int T,N,i,j,max;
    long long profit;
    scanf("%d",&T);
    for(i=0;i<T;i++){
        profit=0;
        max=0;
        scanf("%d",&N);
        for(j=0;j<N;j++){
            scanf("%d",&value_array[j]);
        }
        for(j=N-1;j>=0;j--){
        	if(max<value_array[j])
                max=value_array[j];
            else
                profit=profit+max-value_array[j];
        }
       	printf("#%d %lld\n",i+1,profit);
    }
     
    return 0;
}