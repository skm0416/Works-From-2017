#include<cstdio>

#define MAX_INDEX 300
int N;
int stair[MAX_INDEX + 1] = { 0, };
int sum[MAX_INDEX + 1] = { 0, };


int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

// ? ? o n
// o x o n 이므로 sum[i-3] + stair[i-1]+stair[i]

// ? o x n
// sum[i=2] + stair[i]

int main() {
	scanf("%d",&N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &stair[i]);
	sum[1] = stair[1];
	sum[2] = stair[1] + stair[2];
	sum[3] = max(stair[2] + stair[3], stair[1] + stair[3]);
	for (int i = 3; i <= N; i++) {
		sum[i] = max(sum[i - 2] + stair[i], sum[i - 3] + stair[i - 1] + stair[i]);
	}
	printf("%d\n", sum[N]);

	return 0;
}