#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
	struct Node *prev;
} Node;

void printer(Node *node)
{
	while (node) {
		printf(" -> %d", node->value);
		node = node->next;
	}
	printf("\n");
}

void free_from(Node *node)
{
	while (node) {
		Node *me = node;
		node = node->next;
		free(me);
	}
}

Node *new_node(int value)
{
	Node *nn = calloc(1,sizeof(Node *));
	nn->value = value;
	return nn;
}

Node *add(Node *node, int value)
{
	Node *nn = new_node(value);
	if (!node) return nn;
	nn->next = node;
	node->prev = nn;
	return nn;
}

Node *push(Node *node, int value)
{
	Node *nn = calloc(1, sizeof(Node *));
	nn->value = value;
	if (!node) return nn;
	Node *head = node;
	while (node->next) node = node->next;
	nn->prev = node;
	node->next = nn;
	return head;
}

Node *insert(Node *node, int value, int index)
{
	if (!node || index < 0) return node;
	Node *head = node;
	int i = 0;
	while (node->next && i < index) {
		++i;
		node = node->next;
	}
	if (i < index) return head;
	Node *nn = calloc(1, sizeof(Node *));
	nn->value = value;
	nn->prev = node->prev; // set previous node to be 'prev' for the new node
	node->prev->next = nn; // set previous node's 'next' to be the new node

	node->prev = nn; // set the current node's 'prev' to be the new node
	nn->next = node; // set the current node to be the 'next' for the new node
	return head;
}

Node *pop_front(Node *node)
{
	if (!node) return node;
	if (!node->next) {
		free(node);
		return 0;
	}
	Node *new_head = node->next;
	new_head->prev = 0;
	free(node);
	return new_head;
}

Node *pop_back(Node *node)
{
	if (!node) return node;
	Node *head = node;
	while (node->next) node = node->next;
	node->prev->next = 0; // set previous node's 'next' to null
	free(node);
	return head;
}

Node *pop_index(Node *node, int index)
{
	if (!node || index < 0) return node;
	if (!index) {
		Node *new_head = node->next;
		free(node);
		return new_head;
	}
	Node *head = node;
	int i = 0;
	while (node->next && i < index) {
		++i;
		node = node->next;
	}
	if ( i < index) return head;
	Node *me = node;
	node->prev->next = (node->next) ? node->next : 0; // set previous node's 'next' to be the next node
	if (node->next) node->next->prev = node->prev; // set next node's 'prev' to be the prev node, if it exists
	free(me);
	return head;
}
	

int main(void)
{
	Node *head = new_node(2);
	printer(head);
	head = add(head, 1);
	printer(head);
	head = push(head, 3);
	printer(head);
	head = push(head, 5);
	printer(head);
	head = insert(head, 4, 3);
	head = insert(head, 4, -1);
	head = insert(head, 4, 100);
	printer(head);

	printer(head);
	head = pop_front(head);
	printer(head);
	head = pop_back(head);
	printer(head);
	head = pop_index(head, -1);
	head = pop_index(head, 1);
	printer(head);
 	head = pop_index(head, 1);
	printer(head);
	head = pop_index(head,0);
	printer(head);

	free_from(head);
}