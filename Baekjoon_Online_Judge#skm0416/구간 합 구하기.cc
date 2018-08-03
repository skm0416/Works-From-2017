#include<stdio.h>
long long tree[3000001] = { 0, };
int log = 1, N, M, K, count = 0;
int first, a, b;

void change(int target, int value) {
	int index = log - 1 + target;
	int delta = value - tree[index];
	tree[index] = value;
	while (index > 1) {
		index = index / 2;
		tree[index] = tree[index] + delta;
	}
}
long long get(int node, int left, int right, int start, int end) {
	if (end<left || start>right) return 0;
	if (left <= start && end <= right) return tree[node];
	return get(node * 2, left, right, start, (end + start) / 2) +
		get(node * 2 + 1, left, right, ((start + end) / 2) + 1, end);
}


void sum(int left, int right) {
	long long sum = get(1, left, right, 1, log);

	printf("%lld\n",sum);
}

int main() {
	scanf("%d %d %d", &N,&M,&K);
	while (N > log) {
		log = log * 2;
		count++;
	}
	for (int i = 0; i < N; i++) {
		scanf(" %d", &tree[log + i]);
	}
	for (int j = log - 1; j > 0; j--) {
		tree[j] = tree[j * 2] + tree[j * 2 + 1];
	}
	/*
	for (int k = 1; k < log*2; k++)
		printf("%d\n", tree[k]);
	
	*/
	for (int k = 0; k < M + K; k++) {
		scanf(" %d %d %d", &first, &a, &b);
		if (first == 1)
			change(a, b);
		else if (first == 2)
			sum(a, b);
	}


	return 0;
}