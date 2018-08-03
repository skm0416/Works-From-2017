#include<stdio.h>
#include<limits.h>
int N, H;
int top[500001];
int down[500001];
int top_total[500001] = { 0, };
int down_total[500001] = { 0, };
int total[500001];
int min = INT_MAX;

int getmin(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}

int main() {
	int temp, count=0;

	scanf("%d %d", &N, &H);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &temp);
		if (i % 2 == 1) {
			down[temp]++;
		}
		else {
			top[temp]++;
		}
	}
	for (int i = H; i >= 1; i--) {
		top_total[i] = top_total[i + 1] + top[i];
		down_total[i] = down_total[i + 1] + down[i];
	}
	for (int i = 1; i <= H; i++) {
		total[i] = down_total[i] + top_total[H - i +1];
		min = getmin(min, total[i]);
	}
	for (int i = 1; i <= H; i++)
		if (total[i] == min)
			count++;
	printf("%d %d", min,count);
	

	return 0;
}