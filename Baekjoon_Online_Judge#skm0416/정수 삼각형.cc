#include<cstdio>

#define MAX_VALUE 500
int N;
int triangle[MAX_VALUE + 1][MAX_VALUE + 1];
int sum[MAX_VALUE + 2][MAX_VALUE + 2] = { 0, };

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++)
			scanf("%d", &triangle[i][j]);
	}
	sum[1][1] = triangle[1][1];
	for (int i = N; i >= 1; i--) {
		for (int j = i; j >= 1; j--) {
			sum[i][j] = max(sum[i + 1][j], sum[i + 1][j + 1]) + triangle[i][j];
		}
	}
	printf("%d\n", sum[1][1]);


	return 0;
}