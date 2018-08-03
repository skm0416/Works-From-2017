#include<cstdio>
#include<list>
#include<cmath>

using namespace std;
#define N 4000000

list<int> primes;
list<int>::iterator it_start;
list<int>::iterator it_now;

bool isChecked[N+1] = { false, };

int main() {
	int eraser, input, sum, count = 0;
	scanf("%d", &input);
	for (int i = 2; i <= input; i++) {
		if (isChecked[i] == false) {
			isChecked[i] = true;
			primes.push_back(i);
			eraser = i * 2;
			while (eraser <= input) {
				if (isChecked[eraser] == false)
					isChecked[eraser] = true;
				eraser += i;
			}
		}
	}
	for (it_start = primes.begin(); it_start != primes.end(); it_start++) {
		sum = 0;
		for (it_now = it_start; sum < input && it_now != primes.end(); it_now++)
			sum += *it_now;
		if (sum == input)
			count++;
	}
	printf("%d\n", count);

	return 0;
}