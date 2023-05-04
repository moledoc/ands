#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

void free_from(Node *node)
{
	if (!node) return;
	if (!node->next) {
		free(node);
		return;
	}
	Node *head = node; // save head, will be freed last
	node = head->next; // move on to next node
	head->next = 0; // make next from head NULL, so that while loop exits
	while(node) {
		Node *me = node;
		node = node->next;
		free(me);
	}
}

void printer(Node *node)
{
	if (!node) {
		printf("\n");
		return;
	}
	Node *head = node;
	do {
		printf(" -> %d", node->value);
		node = node->next;
	} while (node != head && node);
	if (!node) {printf(" (head)\n");return;}
	printf(" -> %d (head)\n", node->value);
}

// NOTE: only difference between 'add' and 'push' is that 'add' returns the new node as 'head' and 'push' returns the existing head as 'head'

Node *add(Node *node, int value)
{
	Node *new_head = calloc(1, sizeof(Node *));
	new_head->value = value;
	new_head->next = new_head; // init next value with itself in case it will be the only element
	if (!node) return new_head;
	Node *old_head = node;
	while (node->next != old_head && node->next) node = node->next;
	node->next = new_head;
	new_head->next = old_head;
	return new_head;
}

Node *push(Node *node, int value)
{
	Node *new_node = calloc(1, sizeof(Node *));
	new_node->value = value;
	new_node->next = new_node; // init next value with itself in case it will be the only element
	if (!node) return new_node;
	Node *head = node;
	while (node->next != head && node->next) node = node->next;
	node->next = new_node;
	new_node->next = head;
	return head;
}

Node *insert(Node *node, int value, int index)
{
	if (!node) return node;
	if (index == 0) {
		return add(node, value);
	}
	Node *head = node;
	int i = 1;
	while (node->next && node->next != head && i < index) {
		node = node->next;
		++i;
	}
	if ( i < index ) return head;
	Node *new_node = calloc(1, sizeof(Node *));
	new_node->value = value;
	new_node->next = node->next;
	node->next  = new_node;
	return head;
}


Node *pop_front(Node *node)
{
	if (!node) return node;
	Node *head = node;
	Node *new_head = head->next;
	while (node->next && node->next != head) node = node->next;
	node->next = new_head;
	free(head);
	return new_head;
}


Node *pop_back(Node *node)
{
	if (!node) return node;
	Node *head = node;
	while (node->next && node->next->next != head) node = node->next;
	Node *me = node->next;
	node->next = head;
	free(me);
	return head;
}


Node *pop_index(Node *node, int index)
{
	if (!node) return node;
	if (index == 0) return pop_front(node);
	Node *head = node;
	int i = 1;
	while (node->next && i < index) {
		node = node->next;
		++i;
	}
	if (i<index) return head;
	Node *me = node->next;
	node->next = me->next;
	free(me);
	return head;		
}

int main(void)
{
	Node *head = calloc(1, sizeof(Node *));
	printer(head);
	free_from(head);

	printf("----------------------\n");
	head = calloc(1, sizeof(Node *));
	head = insert(head, 21, 0);
	printer(head);
	free_from(head);

	printf("----------------------\n");
	head = calloc(1, sizeof(Node *));
	head = add(head, 2);
	head = add(head, 3);
	head = add(head, 4);
	printer(head);
	head = push(head, 12);
	head = push(head, 13);
	printer(head);
	head = insert(head, 21, 5);
	printer(head);
	head = insert(head, 22, 3);
	printer(head);

	printf("----------------------\n");
	head = pop_front(head);
	printer(head);
	head = pop_back(head);
	printer(head);
	head = pop_index(head, 0);
	printer(head);
	head = pop_index(head, 4);
	printer(head);
	head = pop_index(head, 2);
	printer(head);

	free_from(head);
}