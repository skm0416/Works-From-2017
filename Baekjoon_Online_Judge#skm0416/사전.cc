#include<cstdio>

#define MAX_VALUE 200
#define KMAX 1000000000
long long N, M, K;
long long pascal[MAX_VALUE + 1][MAX_VALUE + 1] = { 0, };
bool output[MAX_VALUE + 1] = { false, };

void print_result() {
	for (int i = N+M; i >= 1; i--) {
		if (output[i])
			printf("z");
		else
			printf("a");
	}
	printf("\n");
}

int main() {
	scanf("%lld %lld %lld", &N, &M, &K);
	pascal[0][0] = 1;
	for (int i = 1; i <= N + M; i++) {
		pascal[i][0] = 1;
		for (int j = 1; j <= M; j++) {
			pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
			if (pascal[i][j] >= KMAX)
				pascal[i][j] = KMAX + 1;
		}
	}
	long long left = N + M;
	long long right = M;
	long long value = K;
	if (value > pascal[left][right]) {
		printf("-1\n");
		return 0;
	}

	while (value>0 && left>0) {
		if (value > pascal[left - 1][right]) {
			output[left] = true;
			value = value - pascal[left - 1][right];

			right--;
		}
		left--;
	}
	print_result();

	return 0;
}