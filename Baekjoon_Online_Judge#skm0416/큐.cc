#include<stdio.h>
#include<queue>

std::queue<int> queue;

int main() {
	int N, temp_number;
	char temp[10];
	scanf("%d ", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", &temp);
		if (temp[3] == 'h') {//push
			scanf("%d", &temp_number);
			queue.push(temp_number);
		}
		else if (temp[0] == 'f') {//front
			if (queue.size() > 0) {
				printf("%d\n", queue.front());
			}
			else
				printf("-1\n");
		}
		else if (temp[0] == 'b') {//back
			if (queue.size() > 0)
				printf("%d\n", queue.back());
			else
				printf("-1\n");
		}
		else if (temp[0] == 's') {//size
			printf("%d\n", queue.size());
		}
		else if (temp[0] == 'e') {//empty
			if (queue.size()>0)
				printf("0\n");
			else
				printf("1\n");
		}
		else if (temp[0] == 'p') {//pop
			if (queue.size() > 0) {
				printf("%d\n", queue.front());
				queue.pop();
			}
			else
				printf("-1\n");
		}
	}

	return 0;
}