#include <string>
#include <vector>

using namespace std;
vector<vector<int>> mat;
int N;
int L,R,D,U,now,count=0;

int min(int a, int b){
    if(a<b)
        return a;
    else
        return b;
}

int max(int a, int b){
    if(a>b)
        return a;
    else
        return b;
}

void find_3x2(int target){
    L = N-1;
    U = N-1;
    R = 0;
    D = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(mat[i][j] == target){
                L = min(L,j);
                R = max(R,j);
                U = min(U,i);
                D = max(U,i);
            }
        }
    }
}

void delete_3x2(int target){
    count +=1;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(mat[i][j] == target){
                mat[i][j] = 0;
            }
        }
    }
}
bool check_up(int y, int x,int target){
    for(int i=0; i<y; i++){
        if(mat[i][x] != 0)
            return false;
    }
    return true;
}

bool check_3x2(int target){
    //printf("%d %d %d %d\n",L,R,D,U);
    for(int Y=U; Y<=D; Y++){
        for(int X=L; X<=R; X++){
            if(mat[Y][X] != target){
                if(mat[Y][X] != 0)
                    return false;
                else if(!check_up(Y,X,target))
                    return false;
            }
        }
    }
    //printf("check %d passed\n",target);
    return true;
}
int solution(vector<vector<int>> board) {
    mat = board;
    N = board.size();
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(mat[i][j] != 0){
                now = mat[i][j];
                find_3x2(now);
                if(check_3x2(now)){
                    delete_3x2(now);
                    i = max(i-2,0);
                }
                    
            }
        }
    }
    int answer = count;
    return answer;
}