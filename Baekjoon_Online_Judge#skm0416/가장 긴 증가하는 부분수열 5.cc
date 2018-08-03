#include<cstdio>
#include<list>

#define MAX_INDEX 1000000
using namespace std;
int lis[MAX_INDEX + 2];
int N, lis_size = 0;
int pos[MAX_INDEX + 2];
int value[MAX_INDEX + 2];
list<int> output;
list<int>::iterator outit;

int lower_bound(int value) {
	int output = 0;
	for (int i = 0; i < lis_size+1; i++) {
		output = i;
		if (lis[i] >= value)
			break;
	}
	return output;
}


int main() {
	scanf("%d", &N);
	int temp, end = -1000000001, search = 0, target;

	scanf("%d", &temp);
	lis[0] = temp;
	pos[1] = lis_size;
	value[1] = temp;

	for (int i = 2; i <= N; i++) {
		scanf("%d", &temp);
		if (temp > lis[lis_size]) {
			pos[i] = ++lis_size;
			lis[lis_size]=temp;
		}
		else {
			pos[i] = lower_bound(temp);
			lis[pos[i]] = temp;
		}
		value[i] = temp;
	}

	printf("%d\n", lis_size+1);

	for (int i = N; i >= 1; i--) {

		if (lis_size == pos[i]) {
			lis_size--;
			output.push_front(value[i]);
		}
	}
	for (outit = output.begin(); outit != output.end(); outit++)
		printf("%d ", *outit);

	return 0;
}