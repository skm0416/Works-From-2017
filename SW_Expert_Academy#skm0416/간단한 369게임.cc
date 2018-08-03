#include<stdio.h>

int main(){
	int N,i,target,clap,temp;
    scanf("%d",&N);
    for(i=1;i<=N;i++){
    	clap=0;
        target=i;
        while(target>0){
            temp = target%10;
        	if(temp%3==0&&temp!=0)
                clap++;
            target=target/10;
        }
        if(clap==0){
        	printf("%d",i);
        }
        else{
        	for(;clap>0;clap--)
                printf("-");
        }
        printf(" ");
    }
	return 0;
}