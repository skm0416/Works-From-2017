#include<iostream>
#include<map>
using namespace std;
 
int check[1001];
int land,clue,limit;
multimap<int,int> clue_map;
 
void search_land(int now, int time){
    if(check[now] == -1 || check[now] > time){
        check[now] = time;
        multimap<int,int>::iterator iter;
        for(iter = clue_map.equal_range(now).first; iter != clue_map.equal_range(now).second; iter++){
            search_land(iter->second,time+1);
        }
    }
}
  
  
int main(){
    int T,first,second;
      
    scanf("%d",&T);
    for(int i=0; i<T; i++){
        clue_map.clear();
        for(int k=0; k<1001; k++){
            check[k] = -1;
        }
        scanf("%d",&land);
        scanf("%d",&clue);
        scanf("%d",&limit);
        for(int j=0; j<clue; j++){
            scanf("%d",&first);
            scanf("%d",&second);
            clue_map.insert(pair<int,int>(first,second));
        }
        search_land(1,0);
         
        if(check[land] == -1 || check[land] > limit)
            printf("#%d -1\n",i+1);
        else
            printf("#%d %d\n",i+1,check[land]);
    }
      
    return 0;
}