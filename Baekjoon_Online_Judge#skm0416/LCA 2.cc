#include<cstdio>
#include<queue>
#include<list>

using namespace std;

#define KMAX 17 // 2^17 = 131072
int depth[100001] = { 0, };
int depthmap[100001][KMAX+1] = { 0, };

list<int> Lines[100001];
list<int>::iterator it;
queue<int> que;

int main() {
	int a, b, N, M, target, now;

	scanf("%d", &N);
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &a, &b);
		Lines[a].push_back(b);
		Lines[b].push_back(a);
	}

	depth[1] = 1;
	depthmap[1][0] = 1;
	que.push(1);
	while (!que.empty()) {
		target = que.front();
		que.pop();
		for (it = Lines[target].begin(); it != Lines[target].end(); it++) {
			now = *it;
			if (depth[now] == 0) {
				depth[now] = depth[target] + 1;
				depthmap[now][0] = target;
				que.push(now);
			}
		}

	}

	for (int j = 1; j <= KMAX; j++) {
		for (int i = 1; i <= N; i++) {
			depthmap[i][j] = depthmap[depthmap[i][j - 1]][j - 1];
		}
	}
	scanf("%d", &M);
	for (int j = 0; j < M; j++) {
		scanf("%d %d", &a, &b);
		if (depth[a] > depth[b]) {
			for (int k = KMAX; k >= 0; k--) {
				if (a != b && depth[depthmap[a][k]] >= depth[b])
					a = depthmap[a][k];
			}
		}
		else if (depth[a] < depth[b]) {
			for (int k = KMAX; k >= 0; k--) {
				if (a != b && depth[depthmap[b][k]] >= depth[a])
					b = depthmap[b][k];
			}
		}
		int ans;

		for (int k = KMAX; k >= 0; k--) {
			if (a != b && depthmap[a][k] != depthmap[b][k]) {
				a = depthmap[a][k];
				b = depthmap[b][k];
			}
		}
		if (a == b)
			ans = a;
		else
			ans = depthmap[a][0];
		printf("%d\n", ans);
	}
	return 0;
}