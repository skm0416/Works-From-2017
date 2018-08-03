#include<cstdio>
#include<list>

using namespace std;

list<int> primes;
list<int>::iterator it;

short isChecked[1000001] = { 0, };

int main() {
	int N = 1000000, eraser, input;
	for (int i = 2; i <= N; i++) {
		if (isChecked[i] == 0) {
			isChecked[i] = 1;
			primes.push_back(i);
			eraser = i * 2;
			while (eraser <= N) {
				if (isChecked[eraser] == 0)
					isChecked[eraser] = 2;
				eraser += i;
			}
		}
	}
	while (1) {
		scanf("%d", &input);
		if (input == 0)
			break;
		for (it = primes.begin(); it != primes.end(); it++) {
			if (isChecked[input-*it]==1)
				break;
		}
		printf("%d = %d + %d\n",input, *it, input - *it);
	}

	return 0;
}