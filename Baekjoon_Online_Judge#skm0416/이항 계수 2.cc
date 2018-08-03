#include<cstdio>

#define mod 10007
#define MAX_VALUE 1000
int pascal[MAX_VALUE+1][MAX_VALUE+1] = { 0, };

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int main() {
	int N, K;

	scanf("%d %d", &N, &K);
	pascal[0][0] = 1;
	for (int i = 1; i <= N; i++) {
		pascal[i][0] = 1;
		for (int j = 1; j <= max(i,K); j++) {
			pascal[i][j] = pascal[i - 1][j - 1] % mod + pascal[i - 1][j] % mod;
		}
	}
	printf("%d\n", pascal[N][K] % mod);
	
	return 0;
}