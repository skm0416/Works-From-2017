#include<stdio.h>
#include<queue>
#include<list>

std::queue<int> queue;
int N, M;
std::list<int> root[32001];
short degree[32001] = { 0, };

int main() {
	int A, B, temp,target;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf(" %d %d", &A, &B);
		root[A].push_back(B);
		degree[B]++;
	}
	for (int j = 1; j <= N; j++) {
		if (degree[j] == 0)
			queue.push(j);
	}

	while (!queue.empty()) {
		temp = queue.front();
		printf("%d ", temp);
		queue.pop();
		while(root[temp].size()>0){
			target = root[temp].front();
			root[temp].pop_front();
			if (degree[target]-- == 1)//0이 될 예정
				queue.push(target);
		}
	}

	return 0;
}