#include<cstdio>

bool isChecked[1001] = { false, };

int main() {
	int N, K, deleted, count = 0, eraser, plus;
	scanf("%d %d", &N, &K);
	for (int j = 2; count < K && j <= N; j++) {
		if (isChecked[j] == false) {
			isChecked[j] = true;
			deleted = j;
			plus = deleted;
			count++;
			eraser = deleted * 2;
			while (count < K && eraser <= N) {
				if (isChecked[eraser] == false) {
					isChecked[eraser] = true;
					count++;
					deleted = eraser;
				}
				eraser += plus;
			}
		}
	}
	printf("%d\n", deleted);

	return 0;
}