#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

void printer(Node *node)
{
	if (!node) return;
	while(node) {
		printf(" -> %d", node->value);
		node = node->next;
	}
	printf("\n");
}

void free_from(Node *node)
{
	if (!node) return;
	while (node) {
		Node *me = node;
		node = node->next;
		free(me);
	}
}

Node *push(Node *tail, int value)
{
	Node *new_tail = calloc(1, sizeof(Node *));
	new_tail->value = value;
	if (!tail) return new_tail;
	tail->next = new_tail;
	return new_tail;
}

Node *pop(Node *head)
{
	if (!head) return head;
	Node *new_head = head->next;
	free(head);
	return new_head;
}

int main(void)
{
	Node *head = calloc(1, sizeof(Node *));
	Node *tail = push(head, 1);
	tail = push(tail, 2);
	tail = push(tail, 3);
	printer(head);
	head = pop(head);
	printer(head);
	head = pop(head);
	printer(head);
	free_from(head);
}
