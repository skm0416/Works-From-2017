#include<cstdio>

#define MAX_VALUE 30

long long pascal[MAX_VALUE + 1][MAX_VALUE + 1] = { 0, };

	int main() {
		pascal[0][0] = 1;
		for (int i = 1; i <= MAX_VALUE; i++) {
			pascal[i][0] = 1;
			for (int j = 1; j <= i; j++) {
				pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
			}
		}
	int N, M, T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d", &N, &M);
		printf("%lld\n", pascal[M][N]);
	}
	return 0;
}