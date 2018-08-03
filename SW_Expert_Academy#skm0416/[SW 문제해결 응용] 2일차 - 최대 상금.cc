#include<stdio.h>
#include<string.h>
#include<algorithm>
int N,output;
char array[7];
void swap(int a, int b){
    int temp=array[b];
    array[b] = array[a];
    array[a] = temp;
}
void bigger(){
    int number = 0;
    for(int i=0;i<N;i++){
        number=number*10 + array[i]-'0';
    }
    if(number>output)
        output=number;
}
 
void change_number(int change){
    if(change>0){
        int i,j;
        for(i=0;i<N;i++){
            for(j=i+1;j<N;j++){
                swap(i,j);
                change_number(change-1);
                swap(i,j);
            }
        }
    }
    else
        bigger();
}
 
int main(){
    int T,change;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%s %d",array,&change);
        N = strlen(array);
        output = 0;
        if(N-1>change)
        	change_number(change);
        else{
        	std::sort(array,array+N);
            std::reverse(array,array+N);
            if((change+1-N)%2==1)
                change_number(1);
            else
            	bigger();
        }
        printf("#%d %d\n",i,output);
    }
    return 0;
}