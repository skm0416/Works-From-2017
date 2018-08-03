#include<stdio.h>
int tree[1000001];

int maximum(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}
int main() {
	int N, M, output=0, max = 0, min = 0, mid;
	long long sum;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &tree[i]);
		max = maximum(max, tree[i]);
	}
	while (min <= max) {
		mid = (min + max) / 2;
		sum = 0;
		for (int i = 0; i < N; i++) {
			if (mid < tree[i])
				sum = sum + tree[i] - mid;
		}
		if (sum >= M) {
			if (output < mid)
				output = mid;
			min = mid + 1;
		}
		else
			max = mid - 1;
	}
	printf("%d", output);
	return 0;
}