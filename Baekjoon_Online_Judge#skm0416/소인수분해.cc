#include<cstdio>
#include<cmath>

#define N 10000000

bool isChecked[N + 1] = { false, };

int main() {
	int eraser, value, input, root;
	scanf("%d", &input);
	value = input;
	root = sqrt(input);
	for (int i = 2; value > 1 && i <= root; i++) {
		if (isChecked[i] == false) {
			isChecked[i] = true;
			while (value%i == 0) {
				value = value / i;
				printf("%d\n", i);
			}

			eraser = i * 2;
			while (eraser <= root) {
				if (isChecked[eraser] == false)
					isChecked[eraser] = true;
				eraser += i;
			}
		}
	}
	if (value != 1)
		printf("%d\n", value);
	return 0;
}