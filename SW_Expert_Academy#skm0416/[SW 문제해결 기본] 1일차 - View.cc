#include<stdio.h>
#include<stdlib.h>
int array[1000];

int top(int a,int b,int c,int d){
	int x,y;
    if(a>b)
        x=a;
    else
        x=b;
    if(c>d)
        y=c;
    else
        y=d;
    if(x>y)
        return x;
    else
        return y;
}

int main(){
    int i,j,k,N,sum,high;
    for(i=1;i<=10;i++){
        sum=0;
    	scanf("%d",&N);
        for(j=0;j<N;j++){
        	scanf("%d",&array[j]);
        }
        for(k=2;k<N-2;k++){
        	high=top(array[k-2],array[k-1],array[k+1],array[k+2]);
            if(array[k]>high)
                sum=sum+array[k]-high;
        }
        printf("#%d %d\n",i,sum);
    }
	return 0;
}