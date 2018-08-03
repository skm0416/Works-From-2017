#include<cstdio>
#include<queue>
#include<list>

using namespace std;

#define KMAX 17 // 2^17 = 131072
#define MAX_VALUE 1000001
int depth[100001] = { 0, };
int depthmap[100001][KMAX + 1] = { 0, };
int minmap[100001][KMAX + 1];
int maxmap[100001][KMAX + 1];

list<pair<int,int>> Lines[100001];
list<pair<int,int>>::iterator it;
queue<int> que;

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}
int max(int a, int b) {
	if (a < b)
		return b;
	else
		return a;
}

int main() {
	int a, b, c, N, M, target, now, cost;

	scanf("%d", &N);
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Lines[a].push_back(make_pair(b,c));
		Lines[b].push_back(make_pair(a,c));
	}
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= KMAX; j++) {
			minmap[i][j] = MAX_VALUE;
			maxmap[i][j] = 0;
		}
	}

	depth[1] = 1;
	depthmap[1][0] = 1;
	que.push(1);
	while (!que.empty()) {
		target = que.front();
		que.pop();
		for (it = Lines[target].begin(); it != Lines[target].end(); it++) {
			now = it->first;
			cost = it->second;
			if (depth[now] == 0) {
				depth[now] = depth[target] + 1;
				depthmap[now][0] = target;
				minmap[now][0] = cost;
				maxmap[now][0] = cost;
				que.push(now);
			}
		}

	}

	for (int j = 1; j <= KMAX; j++) {
		for (int i = 1; i <= N; i++) {
			depthmap[i][j] = depthmap[depthmap[i][j - 1]][j - 1];
			maxmap[i][j] = max(maxmap[i][j - 1], maxmap[depthmap[i][j - 1]][j - 1]);
			minmap[i][j] = min(minmap[i][j - 1], minmap[depthmap[i][j - 1]][j - 1]);
		}
	}
	scanf("%d", &M);
	for (int j = 0; j < M; j++) {
		int min_ans = MAX_VALUE;
		int max_ans = 0;
		scanf("%d %d", &a, &b);
		if (depth[a] > depth[b]) {
			for (int k = KMAX; k >= 0; k--) {
				if (a != b && depth[depthmap[a][k]] >= depth[b]) {
					min_ans = min(min_ans, minmap[a][k]);
					max_ans = max(max_ans, maxmap[a][k]);
					a = depthmap[a][k];
				}
			}
		}
		else if (depth[a] < depth[b]) {
			for (int k = KMAX; k >= 0; k--) {
				if (a != b && depth[depthmap[b][k]] >= depth[a]) {
					min_ans = min(min_ans, minmap[b][k]);
					max_ans = max(max_ans, maxmap[b][k]);
					b = depthmap[b][k];
				}
			}
		}
		for (int k = KMAX; k >= 0; k--) {
			if (a != b && depthmap[a][k] != depthmap[b][k]) {
				min_ans = min(min_ans, min(minmap[a][k], minmap[b][k]));
				max_ans = max(max_ans, max(maxmap[a][k], maxmap[b][k]));
				a = depthmap[a][k];
				b = depthmap[b][k];
			}
		}
		if (a != b) {
			min_ans = min(min_ans, min(minmap[a][0], minmap[b][0]));
			max_ans = max(max_ans, max(maxmap[a][0], maxmap[b][0]));
		}
		printf("%d %d\n", min_ans,max_ans);
	}
	return 0;
}