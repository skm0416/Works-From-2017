#include<cstdio>
#include<climits>
#include<list>
#include<set>

using namespace std;

int V, E;
int Cost[20001];
int Start;
list<pair<int, int>> Line[20001]; //cost, target
list<pair<int, int>>::iterator it;
pair<int, int> target;
int vertex;
multiset<pair<int, int>> queue;


int main() {
	int a, b, c;

	scanf("%d %d", &V, &E);
	scanf("%d", &Start);
	for (int i = 1; i <= V; i++)
		Cost[i] = INT_MAX;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);// a->b cost c
		Line[a].push_back(make_pair(c, b));
	}
	Cost[Start] = 0;
	queue.insert(make_pair(0, Start));
	while (!queue.empty()) {
		target = *queue.begin();
		queue.erase(target);
		vertex = target.second;
		for (it = Line[vertex].begin(); it != Line[vertex].end(); it++) {
			if (Cost[it->second] > Cost[vertex] + it->first) {
				Cost[it->second] = Cost[vertex] + it->first;
				queue.insert(make_pair(Cost[it->second],it->second));
			}
		}
	}
	for (int i = 1; i <= V; i++) {
		if (Cost[i] == INT_MAX)
			printf("INF\n");
		else
			printf("%d\n", Cost[i]);
	}

	return 0;
}