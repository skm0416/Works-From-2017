#include<cstdio>

#define MAX_INDEX 1024

int matrix[MAX_INDEX + 1][MAX_INDEX + 1] = { 0, };

int main() {
	int N, M, x1, y1, x2, y2, sum;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &matrix[i][j]);
			matrix[i][j] = matrix[i][j] + matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
		}
	}

	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		sum = matrix[x2][y2] - matrix[x2][y1 - 1] - matrix[x1 - 1][y2] + matrix[x1 - 1][y1 - 1];
		printf("%d\n", sum);
	}
}