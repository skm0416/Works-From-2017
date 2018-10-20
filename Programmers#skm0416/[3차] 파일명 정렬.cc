#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<string>> detail;
vector<string> temp(3);
vector<int> sorted;

void cutstring(string target){
    int pos_start = target.find_first_of("0123456789");
    int pos_end = target.find_last_of("0123456789");
    string head = target.substr(0,pos_start);
    string number = target.substr(pos_start,pos_end - pos_start +1);
    string tail = target.substr(pos_end+1);
    for(int i=0; i<head.size(); i++)
        head[i] = toupper(head[i]);
    //cout<<target<<endl;
    //cout<<head<<endl;
    //cout<<number<<endl;
    //cout<<tail<<endl;
    temp[0] = head;
    temp[1] = number;
    temp[2] = tail;
    detail.push_back(temp);
}

bool compare(int a, int b){
    if(detail[a][0] < detail[b][0])
        return true;
    else if(detail[a][0] == detail[b][0])
        return stoi(detail[a][1])<stoi(detail[b][1]);
    else
        return false;
}

vector<string> solution(vector<string> files) {
    for(int i=0; i<files.size(); i++){
        sorted.push_back(i);
        cutstring(files[i]);
    }
    /*
    for(int i=0; i<detail.size(); i++){
        cout<<detail[i][0]<<endl;
        cout<<detail[i][1]<<endl;
        cout<<detail[i][2]<<endl;
        cout<<endl;
    }
    */
    stable_sort(sorted.begin(),sorted.end(),compare);
    vector<string> answer;
    for(int i=0; i<sorted.size(); i++){
        answer.push_back(files[sorted[i]]);
    }
    return answer;
}