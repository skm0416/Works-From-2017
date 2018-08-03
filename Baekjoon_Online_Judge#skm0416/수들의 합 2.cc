#include<stdio.h>
int numbers[10000];
int main() {
	int N, M,sum = 0, start, end, count = 0;
	scanf("%d %d", &N,&M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &numbers[i]);
	}
	for (start = 0,end=0; start < N && end<N;) {
		for (; sum < M && end < N; end++) {
			sum = sum + numbers[end];
		}
		for (; sum >= M; start++) {
			if (sum == M)
				count++;
			sum = sum - numbers[start];
		}
	}
	printf("%d\n", count);

	return 0;
}