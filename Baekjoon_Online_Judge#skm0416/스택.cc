#include<stdio.h>
#include<stdlib.h>


typedef struct node {
	int number;
	node *next;
} node;

int main() {
	int size = 0,N,temp_number;
	char temp[10];
	node* target = (node*)malloc(sizeof(node));
	scanf("%d ", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", &temp);
		if (temp[3] == 'h') {//push
			scanf("%d", &temp_number);
			node* temp_node = (node*)malloc(sizeof(node));
			temp_node->number = temp_number;
			temp_node->next = target;
			size++;
			target = temp_node;
		}
		else if (temp[0] == 't') {//top
			if (size > 0)
				printf("%d\n", target->number);
			else
				printf("-1\n");
		}
		else if (temp[0] == 's') {//size
			printf("%d\n", size);
		}
		else if (temp[0] == 'e') {//empty
			if(size>0)
				printf("0\n");
			else
				printf("1\n");
		}
		else if (temp[0] == 'p') {//pop
			if (size > 0) {
				printf("%d\n", target->number);
				node* temp = target;
				target = target->next;
				free(temp);
				size--;
			}
			else
				printf("-1\n");
		}
	}

	return 0;
}