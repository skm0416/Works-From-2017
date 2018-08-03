#include<cstdio>

int main() {
	int x1, y1, x2, y2, x3, y3, CCW;
	scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
	CCW = x1*y2 + x2*y3 + x3*y1 - x1*y3 - x2*y1 - x3*y2;
	if (CCW == 0)
		printf("0");
	else if (CCW > 0)
		printf("1");
	else
		printf("-1");
}