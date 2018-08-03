#include<cstdio>

#define MAX_INDEX 1000
int N, M;
char matrix[MAX_INDEX + 2][MAX_INDEX + 2];
int dp[MAX_INDEX + 2][MAX_INDEX + 2] = { 0, };

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}


int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", matrix[i]+1);
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (matrix[i][j] == '1') {
				dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
				ans = max(ans, dp[i][j]);
			}
		}
	}
	printf("%d\n", ans*ans);
	
	return 0;
}