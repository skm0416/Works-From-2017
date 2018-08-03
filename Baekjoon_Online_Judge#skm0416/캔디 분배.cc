#include<cstdio>

#define overflow 1000000000
long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a%b);
}

// K * X +1 = C * Y
// C * Y % K * X = 1
// A * s + B * t = 1
// return Y;
long long euclid(long long A, long long B) {
	long long r, q, s, s1 = 1, s2 = 0, t, t1 = 0, t2 = 1, plus = A;

	while (B != 0) {
		// r = r1 - q * r2
		// r = A - x * B
		q = A / B;
		r = A%B;
		
		s = s1 - q * s2;
		s1 = s2;
		s2 = s;

		t = t1 - q * t2;
		t1 = t2;
		t2 = t;

		A = B;
		B = r;
	}
	while (t1 < 0)
		t1 += plus;
	return t1;
}


int main() {
	long long t, K, C;
	scanf("%lld", &t);
	for (int i = 0; i < t; i++) {
		scanf("%lld %lld",&K, &C);
		if (C == 1) {
			if (K >= overflow)
				printf("IMPOSSIBLE\n");
			else
				printf("%lld\n", K + 1);
		}
		else if(K==1){
			printf("1\n");
		}
		else if(gcd(K,C) != 1)
			printf("IMPOSSIBLE\n");
		else {
			long long ans = euclid(K, C);
			if (ans > overflow)
				printf("IMPOSSIBLE\n");
			else
				printf("%lld\n", ans);
		}
	}
	return 0;
}