#include <string>
#include <vector>
#include <set>

using namespace std;
struct node{
    int parent = -1;
    int left = -1;
    int right = -1;
    int x = -1;
    int y = -1;
} node[10001];
set<pair<int,pair<int,int>>> nodes;// Y X nodenum
set<pair<int,pair<int,int>>>::reverse_iterator it;
vector<vector<int>> answer;
vector<int> preorder;
vector<int> postorder;
int N,root,node_count = 0;


void set_node(int N, int P, int Y, int X){
    node[N].parent = P;
    node[N].x = X;
    node[N].y = Y;
}

void add_node(int now,int N, int Y, int X){
    if(node[now].x < X){
        if(node[now].right == -1){
            node[now].right = N;
            set_node(N,now,Y,X);
        }
        else
            add_node(node[now].right,N,Y,X);
    }
    else if(node[now].x > X){
        if(node[now].left == -1){
            node[now].left = N;
            set_node(N,now,Y,X);
        }
        else
            add_node(node[now].left,N,Y,X);
    }
}

void explore_pre(int now){
    if(now == -1)
        return;
    preorder.push_back(now);
    explore_pre(node[now].left);
    explore_pre(node[now].right);
}
void explore_post(int now){
    if(now == -1)
        return;
    explore_post(node[now].left);
    explore_post(node[now].right);
    postorder.push_back(now);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    N = nodeinfo.size();
    for(int i=0; i<N; i++)// Y X nodenum
        nodes.insert(make_pair(nodeinfo[i][1],make_pair(nodeinfo[i][0],i+1)));
    it = nodes.rbegin();
    root = it->second.second;
    set_node(root,0,it->first,it->second.first);
    it++;
    for(; it!= nodes.rend(); it++){
        add_node(root,it->second.second,it->first,it->second.first);
        //printf("N %d Y %d X %d\n",it->second.second,it->first,it->second.first);
    }
    explore_pre(root);
    explore_post(root);
    answer.push_back(preorder);
    answer.push_back(postorder);
    return answer;
}