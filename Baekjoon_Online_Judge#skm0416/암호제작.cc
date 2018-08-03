#include<cstdio>

#define N 1000000
bool isChecked[N+1] = { false, };
char input[1000];

int mod(char *S, int p){
	int ret = 0;
	for (int i = 0; S[i]; i++) 
		ret = (ret * 10 + (S[i] - '0')) % p;
	return ret;
}

int main() {
	int eraser, K;
	int checked=0;
	scanf("%s %d", &input, &K);
	for (int i = 2; i < K; i++) {
		if (isChecked[i] == false) {
			isChecked[i] = true;
			if (mod(input,i) == 0) {
				checked = i;
				break;
			}

			eraser = i * 2;
			while (eraser < K) {
				isChecked[eraser] = true;
				eraser += i;
			}
		}
	}
	if (checked == 0)
		printf("GOOD\n");
	else
		printf("BAD %d\n", checked);

	return 0;
}