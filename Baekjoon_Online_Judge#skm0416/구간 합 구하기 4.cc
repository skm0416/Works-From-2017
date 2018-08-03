#include<cstdio>

#define MAX_INDEX 100000
int N, M;
int sum[MAX_INDEX + 1] = { 0, };

int main() {
	int a, b, temp;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &sum[i]);
		sum[i] += sum[i - 1];
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		if (a > b)
			printf("%d\n", sum[a] - sum[b - 1]);
		else
			printf("%d\n", sum[b] - sum[a-1]);
	}


	return 0;
}