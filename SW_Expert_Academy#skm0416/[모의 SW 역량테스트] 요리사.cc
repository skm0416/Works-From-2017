#include <stdio.h>
#include <limits.h>

typedef _Bool bool;
#define true   (_Bool)1
#define false (_Bool)0
int final_output,N;
int array[21][21];
bool selection[21];

int main(void)
{
	int test_case;
	int T;
    int i,j,group_case;
	//freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);
    
    
    
    
	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &N);
        
        for(i = 0; i < N; i++)
        {
            for(j = 0; j < N; j++)
            {
            	scanf("%d",&array[i][j]);
            }
        }
        final_output = INT_MAX;
        split_case(0,0);
        printf("#%d %d\n",test_case,final_output);
        
	}
   
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}
int split_case(int now, int pick)
{
 	if(now<N)
    {
        if(pick*2 == N)
        {
            for(;now<N;now++)
                selection[now] = false;
            caculate_score();
        }
        else if(N-now+pick == N/2)
        {
             for(;now<N;now++)
                 selection[now] = true;
            caculate_score();
        }
        else
        {
            selection[now] = true;
      		split_case(now+1,pick+1);
        	selection[now] = false;
        	split_case(now+1,pick);
        }
    }
    else
    	caculate_score();   
}
int caculate_score()
{
    int half = N/2;
    int true_array[8];
    int false_array[8];
    int i=0,j=0,t=0,f=0;
    int t_score = 0, f_score=0;
    for(;i<N;i++)
    {
        if(selection[i] == true)
        {
            true_array[t++] = i;
        }
        else
            false_array[f++] = i;
    }
    
    for(i=0;i<half;i++)
    {
        for(j=i+1;j<half;j++)
        {
            t_score = t_score + array[true_array[i]][true_array[j]]+array[true_array[j]][true_array[i]];
            f_score = f_score + array[false_array[i]][false_array[j]]+array[false_array[j]][false_array[i]];
        }
    }
	final_output=min(final_output,absolute(t_score,f_score));   
}

int absolute(int A, int B)
{
    if(A>=B)
        return A-B;
    else
        return B-A;
}

int min(int A, int B)
{
	if(A>=B)
        return B;
    else
        return A;
}