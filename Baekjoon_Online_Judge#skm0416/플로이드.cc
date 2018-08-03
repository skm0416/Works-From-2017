#include<cstdio>
#include<climits>

#define MAX_VALUE 10000001
int N, M;
int D[101][101];

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}


int main() {
	int a, b, c;

	scanf("%d", &N);
	scanf("%d", &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			D[i][j] = MAX_VALUE;
		D[i][i] = 0;
	}
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (D[a][b] > c)
			D[a][b] = c;
	}

	for (int mid = 1; mid <= N; mid++) {
		for (int start = 1; start <= N; start++) {
			for (int end = 1; end <= N; end++) {
				if(start!=end)
					D[start][end] = min(D[start][end], D[start][mid] + D[mid][end]);
			}
		}
	}


	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++){
			if (D[i][j] == MAX_VALUE)
				printf("0 ");
			else
				printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}