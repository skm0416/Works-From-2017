#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<queue>
#include<utility>

using namespace std;

int depthmap[100][100];
int resultmap[100][100];
int N;
int xy[2][4] = {0,0,1,-1,1,-1,0,0};
queue< pair<int,int> > Queue;

int main(){
	int T,x,y;
    pair<int,int> target;
    
    scanf("%d",&T);
    for(int i=0; i<T; i++){
    	scanf("%d",&N);
    	for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++){
                scanf("%1d", &depthmap[i][j]);
                resultmap[i][j] = INT_MAX;
            }
        resultmap[0][0]=0;
        Queue.push(make_pair(0,0));
        while(!Queue.empty()){
            target = Queue.front();
            Queue.pop();
            for(int i=0;i<4;i++){
                x = target.first + xy[0][i];
                y = target.second + xy[1][i];
            	if(x>=0 && y>=0 && x<N && y<N && (resultmap[x][y]==INT_MAX || resultmap[x][y] > resultmap[target.first][target.second] + depthmap[x][y])){
                	resultmap[x][y] = resultmap[target.first][target.second] + depthmap[x][y];
                    Queue.push(make_pair(x,y));
                }
            }
        }
        printf("#%d %d\n",i+1,resultmap[N-1][N-1]);
    }
	return 0;
}