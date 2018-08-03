#include<stdio.h>
#include<set>
int N, M;
using namespace std;
set<pair<int, pair<int, int> > > combo;
int unionset[1001];

int find(int node) {
	if (unionset[node] == node)
		return node;
	else
		return unionset[node] = find(unionset[node]);
}

void setunion(int A, int B) {
	int pa = find(A);
	int pb = find(B);
	unionset[pb] = pa;
}
int check(int A, int B) {
	if (find(A) == find(B))
		return 1;
	else
		return 0;
}

int main() {
	int a, b, c, count = 0, sum = 0;
	set<pair<int, pair<int, int> > >::iterator it;
	set<pair<int, int> >::iterator target;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		combo.insert(make_pair(c, make_pair(a, b)));
	}
	for (int i = 1; i <= N; i++) {
		unionset[i] = i;
	}

	while (count < (N - 1)) {
		it = combo.begin();
		if (check(it->second.first, it->second.second) == 0) {
			setunion(it->second.first, it->second.second);
			sum += it->first;
			count++;
		}
		combo.erase(it);
	}
	printf("%d", sum);


	return 0;
}