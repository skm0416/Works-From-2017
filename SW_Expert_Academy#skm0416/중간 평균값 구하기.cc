#include<stdio.h>
#include<stdlib.h>
#include<array>
#include<algorithm>
int compare(const void * A, const void * B){
 	if(*(int*)A > *(int*)B)
        return 1;
    else if (*(int*)A < *(int*)B)
        return -1;
    else
        return 0;
}

int main(){
	int i,j,T,output;
    long long sum;
    //int numbers[10];
    std::array<int,10> numbers;
    scanf("%d",&T);
    for(i=1;i<=T;i++){
        sum=0;
        for(j=0;j<10;j++){
            scanf("%d",&numbers[j]);
        }
        //qsort(numbers,sizeof(numbers)/sizeof(int),sizeof(int),compare);
        std::sort(numbers.begin(),numbers.begin()+10);
        for(j=1;j<9;j++){
            sum = sum+numbers[j];
        }
        output = sum/8;
        if(sum%8>=4)
            output++;
        printf("#%d %d\n",i,output);
    }
    
	return 0;
}