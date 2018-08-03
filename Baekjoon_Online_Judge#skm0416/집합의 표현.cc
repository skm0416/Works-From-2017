#include<stdio.h>
int n, m;
int unionset[1000001];

int find(int node) {
	if (unionset[node] == node)
		return node;
	else 
		return unionset[node] = find(unionset[node]);
}

void set(int A, int B) {
	int pa = find(A);
	int pb = find(B);
	unionset[pb] = pa;
}
void check(int A, int B) {
	if (find(A) == find(B))
		printf("YES\n");
	else
		printf("NO\n");
}


int main() {
	int first,a,b;

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		unionset[i] = i;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &first, &a, &b);
		if (first == 0)
			set(a, b);
		else if (first == 1)
			check(a, b);
	}


	return 0;
}