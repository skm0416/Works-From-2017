#include<iostream>
#include<map>
using namespace std;
 
map<int,int> match;
int segment[28];
int number[4];
int hour,minute;
 
int seg_to_num(int index){
    int output = 0;
    for(int i=0; i<7; i++){
        output = output<<1;
        output = output + segment[index+i];
    }
    if(match.find(output) == match.end())
        return -1;
    else
        return match.find(output)->second;
}
 
void check_num(){
    int temp, temp_h, temp_m;
    for(int i=0; i<4; i++){
        temp = seg_to_num(i*7);
        if(temp==-1)
            return;
        else
            number[i] = temp;
    }
    temp_h = number[0]*10 + number[1];
    temp_m = number[2]*10 + number[3];
     
    if(temp_h>=0 && temp_h<24 && temp_m>=0 && temp_m < 60){
        if(temp_h < hour){
            hour = temp_h;
            minute = temp_m;
        }
        else if(temp_h == hour && temp_m < minute)
            minute = temp_m;
    }
}
 
void change_bit(int index){
    if(segment[index] == 1)
        segment[index] = 0;
    else
        segment[index] = 1;
}
 
 
int main(){
    int T,temp;
     
    match.insert(pair<int,int>(126,0));
    match.insert(pair<int,int>(6,1));
    match.insert(pair<int,int>(91,2));
    match.insert(pair<int,int>(79,3));
    match.insert(pair<int,int>(39,4));
    match.insert(pair<int,int>(109,5));
    match.insert(pair<int,int>(125,6));
    match.insert(pair<int,int>(70,7));
    match.insert(pair<int,int>(127,8));
    match.insert(pair<int,int>(111,9));
     
    scanf("%d",&T);
    for(int i=0; i<T; i++){
        hour = 23;
        minute = 59;
        for(int j=0; j<4; j++){
            for(int k=0; k<7; k++){
                scanf("%d",&segment[j*7+k]);
            }
        }
        check_num();
        for(int j=0; j<28; j++){
            change_bit(j);
            check_num();
            for(int k=j; k<28; k++){
                change_bit(k);
                check_num();
                change_bit(k);
            }
            change_bit(j);
        }
         
        printf("#%d %d %d\n",i+1,hour,minute);
    }
    return 0;
}