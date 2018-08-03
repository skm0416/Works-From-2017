#include<stdio.h>
#include<limits.h>



int main(){
	int map[100][100],T,length,x,y,output_length,output_target,way;
    for(int i=0; i<10; i++){
    	scanf("%d",&T);
        for(int j=0;j<100;j++){
        	for(int k=0;k<100;k++){
            	scanf("%d",&map[j][k]);
            }
        }
        output_length = INT_MAX;
        
        for(int j=0;j<100; j++){
        	if(map[0][j]){
                length = 0;
                x = j;
                y = 1;
                way = 0;
                while(y<100){
                	length++;
                    if(way==0){
                    	if( (x-1)>=0 && map[y][x-1] == 1){
                        	way = -1;
                            x--;
                        }
                        else if( (x+1)<100 && map[y][x+1] == 1){
                        	way = 1;
                            x++;
                        }
                        else
                            y++;
                    }
                    else if(way==1){
                    	if( (x+1)<100 && map[y][x+1] == 1)
                        	x++;
                       	else{
                            way = 0;
                        	y++;
                        }
                    }
                    else if(way==-1){
                    	if( (x-1)>=0 && map[y][x-1] == 1)
                            x--;
                        else{
                        	way = 0;
                            y++;
                        }
                    }
                }
                if(output_length>=length){
                    output_length = length;
                    output_target = j;
                }
            }
        }
        printf("#%d %d\n",T,output_target);
    }
    
    
    
	return 0;
}