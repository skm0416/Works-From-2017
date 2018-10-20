#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;
int N,len;
int answer = 0;
vector<bool> check_set(9,false);
vector<vector<string>> mat;
vector<set<int>> result_set;
set<int> A;
set<int> B;
set<int>::iterator it;
void add_result(){
    set<int> tempset;
    for(int i=0; i<N; i++){
        if(check_set[i])
            tempset.insert(i);
    }
    //cout<<"tempset "<<tempset.size()<<endl;
    result_set.push_back(tempset);
}

void test_set(){
    set<string> testset;
    for(int i=0; i<len; i++){
        string temp = "";
        for(int j=0; j<N; j++){
            if(check_set[j])
                temp += " " + mat[i][j];
        }
        testset.insert(temp);
    }
    if(testset.size() == len){
        //cout<<*testset.begin()<<endl;
        add_result();
    }
}
void find_set(int now){
    if(now == N){
        test_set();
    }
    else{
        check_set[now] = false;
        find_set(now+1);
        check_set[now] = true;
        find_set(now+1);
    }
}

void delete_set(){
    for(int i=0; i<result_set.size(); i++){
        A = result_set[i];
        bool iscorrect = true;
        for(int j=0; j<result_set.size(); j++){
            B = result_set[j];
            if(i != j && A.size() > B.size()){
                int count = 0;
                for(it = B.begin(); it!=B.end(); it++){
                    if(A.find(*it) != A.end()){
                        count +=1;
                    }
                }
                if(count == B.size())
                    iscorrect = false;
            }
        }
        if(iscorrect)
            answer +=1;
    }
}

int solution(vector<vector<string>> relation) {
    mat = relation;
    len = relation.size();
    N = relation[0].size();
    /*
    for(int i=0; i<len; i++){
        for(int j=0; j<N; j++)
            cout<<relation[i][j]<<" ";
        cout<<endl;
    }
    */
    
    find_set(0);
    delete_set();
    return answer;
}