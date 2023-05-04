#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

void printer(Node *node)
{
	while(node) {
		printf(" -> %d", node->value);
		node = node->next;
	}
	printf("\n");
}

void free_from(Node *node)
{
	if (!node) return;
	if (!node->next) {
		free(node);
		return;
	}
	while(node) {
		Node *me = node;
		node = node->next;
		free(me);
	}
}

Node *add(Node *head, int value)
{
	Node *new_head = calloc(1, sizeof(Node *));
	new_head->value = value;
	if (!head) return new_head;
	new_head->next = head;
	return new_head;
}

Node *pop(Node *head)
{
	Node *new_head = head->next;
	free(head);
	return new_head;
}

int main(void)
{
	Node *head = calloc(1, sizeof(Node *));
	head = add(head, 1);
	printer(head);
	head = add(head, 2);
	printer(head);
	head = pop(head);
	printer(head);

	free_from(head);
}