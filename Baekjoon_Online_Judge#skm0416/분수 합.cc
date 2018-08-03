#include<cstdio>

unsigned int gcd(unsigned int a, unsigned int b) {
	if (b == 0)
		return a;
	return gcd(b, a%b);
}

int main() {
	int a, b, c, d;
	int up, down, divide;

	scanf("%d %d %d %d", &a, &b, &c, &d);
	up = a*d + b*c;
	down = b*d;
	divide = gcd(up, down);
	printf("%d %d\n", up/divide, down/divide);

	return 0;
}