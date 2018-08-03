#include<cstdio>
#include<climits>

using namespace std;
int N, M;
int Total[501];
int From[6001];
int To[6001];
int Cost[6001];
bool Cycle = false;


int main() {
	int a, b, c;
	scanf("%d %d", &N, &M);
	Total[1] = 0;
	for (int i = 2; i <= N; i++)
		Total[i] = INT_MAX;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		From[i] = a; To[i] = b; Cost[i] = c;
	}
	for (int j = 1; j < N; j++) {
		for (int i = 1; i <= M; i++) {
			if (Total[From[i]] != INT_MAX && Total[To[i]] > Total[From[i]] + Cost[i])
				Total[To[i]] = Total[From[i]] + Cost[i];
		}
	}
	for (int i = 1; i <= M; i++) {
		if (Total[From[i]] != INT_MAX && Total[To[i]] > Total[From[i]] + Cost[i])
			Cycle = true;
	}
	if (Cycle)
		printf("-1\n");
	else {
		for (int i = 2; i <= N; i++) {
			if (Total[i] == INT_MAX)
				printf("-1\n");
			else
				printf("%d\n", Total[i]);
		}
	}


	return 0;
}