#include<stdio.h>

typedef struct tree {
	char name;
	int left = -19;// .
	int right = -19;// .
} tree;

tree trees[26];
int N;


void pre(int index) {
	printf("%c", (index + 'A'));
	if (trees[index].left != -19)
		pre(trees[index].left);
	if (trees[index].right != -19)
		pre(trees[index].right);
}
void in(int index) {
	if (trees[index].left != -19)
		in(trees[index].left);
	printf("%c", (index + 'A'));
	if (trees[index].right != -19)
		in(trees[index].right);
	
}
void post(int index) {
	if (trees[index].left != -19)
		post(trees[index].left);
	if (trees[index].right != -19)
		post(trees[index].right);
	printf("%c", (index + 'A'));

}


int main() {
	char parent, left, right,temp;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf(" %c %c %c", &parent, &left, &right);
		fflush(stdin);
		trees[parent-'A'].name = parent;
		trees[parent - 'A'].left = left - 'A';
		trees[parent - 'A'].right = right - 'A';
	}
	pre(0);
	printf("\n");
	in(0);
	printf("\n");
	post(0);
	printf("\n");
	return 0;
}