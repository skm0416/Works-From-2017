#include<cstdio>
#include<climits>
#define MAX_INDEX 500

int N;
int mat[MAX_INDEX + 1][2];
int dp[MAX_INDEX + 1][MAX_INDEX + 1] = {};

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}

int main() {
	int a, b;
	scanf("%d", &N);
	
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &mat[i][0], &mat[i][1]);
		dp[i][i] = 0;
	}
	for (int size = 1; size < N; size++) {
		for (int start = 1;size+start <= N; start++) {
			int end = size + start;
			dp[start][end] = INT_MAX;
			for (int mid = start; mid < end; mid++) {
				dp[start][end] = min(dp[start][end], dp[start][mid] + dp[mid + 1][end] + mat[start][0] * mat[mid][1] * mat[end][1]);
			}
		}
	}
	printf("%d\n", dp[1][N]);

	return 0;
}