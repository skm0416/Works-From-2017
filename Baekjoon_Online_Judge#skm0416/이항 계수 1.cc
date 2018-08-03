#include<cstdio>

int main() {
	int N, K;
	long long output = 1;

	scanf("%d %d", &N, &K);
	for (int i = 0; i < K; i++)
		output = output * (N-i);
	for (; K > 1; K--)
		output = output / K;
	printf("%lld\n", output);
	return 0;
}