#include<cstdio>

#define mod 1000000007
#define MAX_VALUE 4000000

long long factorial[MAX_VALUE + 1];

//페르마의 소정리
//a의 p-1승을 모듈러 p 하면 1이 나옴
//a의 p-2승 * a  를 모듈러 p하면 1이 나옴
// = a의 모듈러p 역원은 a의 p-2승

long long mypower(long long base, long long power) {
	long long ret = 1;
	power = power - 2;

	while (power > 0) {
		if (power % 2)
			ret = (ret * base) % mod;
		power = power / 2;
		base = (base * base) % mod;
	}
	return ret;
}

int main() {
	long long N, K;
	long long reverse;
	factorial[0] = 1;

	scanf("%lld %lld", &N, &K);
	for (long long i = 1; i <= N; i++) {
		factorial[i] = (factorial[i - 1] * i) % mod;
	}
	reverse = mypower((factorial[K] * factorial[N-K]) % mod, mod);

	printf("%lld", (factorial[N] * reverse) % mod);
	return 0;
}