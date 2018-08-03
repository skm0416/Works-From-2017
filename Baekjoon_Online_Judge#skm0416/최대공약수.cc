#include<cstdio>
#include<cmath>
#include<list>

#define MAX_VALUE 1000000000
using namespace std;

list<int> A;
list<int> B;
list<int>::iterator it;
bool isChecked[40000 + 1] = { false, };//root(max_value) ~= 32000

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}

int main() {
	int eraser, value, input, root, N, M;
	int Check_A, Check_B;
	long long gcd = 1;
	bool over = false;
	int count;

	root = sqrt(MAX_VALUE);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &value);
		A.push_back(value);
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d", &value);
		B.push_back(value);
	}

	for (int i = 2; i <= root; i++) {
		if (isChecked[i] == false) {
			isChecked[i] = true;
			Check_A = 0;
			Check_B = 0;
			it = A.begin();
			while(it != A.end()) {
				while (*it % i == 0) {
					*it = *it / i;
					Check_A++;
				}
				if (*it == 1)
					A.erase(it++);
				else
					it++;
			}
			it = B.begin();
			while (it != B.end()) {
				while (*it % i == 0) {
					*it = *it / i;
					Check_B++;
				}
				if (*it == 1)
					B.erase(it++);
				else
					it++;
			}
			count = min(Check_A, Check_B);
			for (int j = 0; j < count; j++) {
				gcd = gcd * i;
				if (gcd > MAX_VALUE) {
					over = true;
					gcd = gcd % MAX_VALUE;
				}
			}
			eraser = i * 2;
			while (eraser <= root) {
				isChecked[eraser] = true;
				eraser += i;
			}
		}
	}

	// root N보다 큰 소수 처리
	for (it = A.begin(); it != A.end(); it++) {
		if (*it != 1) {
			for (list<int>::iterator it2 = B.begin(); it2 != B.end(); it2++) {
				if (*it == *it2) {
					gcd = gcd * *it;
					if (gcd > MAX_VALUE) {
						over = true;
						gcd = gcd % MAX_VALUE;
					}
					*it = 1;
					*it2 = 1;
				}
			}
		}
	}


	if (over == true)
		printf("%09lld\n", gcd);
	else
		printf("%lld\n",gcd);


	return 0;
}