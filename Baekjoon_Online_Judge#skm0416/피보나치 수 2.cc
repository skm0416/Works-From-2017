#include<stdio.h>

int main() {
	int N;
	scanf("%d", &N);
	long long fibo[91];
	fibo[2] = 1;
	fibo[1] = 1;
	fibo[0] = 0;
	for (int i = 3; i <= N; i++) {
		fibo[i] = fibo[i - 2] + fibo[i - 1];
	}
	printf("%lld", fibo[N]);
	return 0;
}