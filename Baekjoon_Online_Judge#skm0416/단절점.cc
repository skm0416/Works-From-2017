#include<cstdio>
#include<set>
#include<list>

using namespace std;

bool cutpoint[10001] = { false, };
bool visited[10001] = { false, };
list<int> connected[10001];
int V, E;
int order = 0;
int save_order[10001];

int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

int DFS(int now,int parent) {
	visited[now] = true;
	save_order[now]= ++order;
	int low = save_order[now];
	int child = 0;
	list<int>::iterator it = connected[now].begin();
	for (; it != connected[now].end(); it++) {
		if (*it == parent)
			continue;
		else if (visited[*it] == true)
			low = min(low, save_order[*it]);
		else {
			child++;
			int templow = DFS(*it,now);
			if (parent != -1 && templow >= save_order[now])
				cutpoint[now] = true;
			low = min(low, templow);
		}
	}
	if (parent == -1 && child > 1)
		cutpoint[now] = true;
	return low;
}


int main() {
	int a, b;
	scanf("%d %d", &V, &E);
	for (int i = 0; i < E; i++) {
		scanf("%d %d", &a, &b);
		connected[a].push_back(b);
		connected[b].push_back(a);
	}
	for (int i = 1; i <= V; i++) {
		if (visited[i] == true) continue;
		DFS(i, -1);
	}

	int check = 0;
	for (int i = 1; i <= V; i++)
		if (cutpoint[i] == true)
			check++;
	printf("%d\n", check);
	for (int i = 1; i <= V; i++) {
		if (cutpoint[i] == true)
			printf("%d ", i);
	}
	printf("\n");
	return 0;
}