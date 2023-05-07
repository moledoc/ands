#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
	struct Node *prev;
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
	} while (node && node != head);
	if (!node) {printf(" (head)\n"); return;}
	printf(" -> %d (head)\n", node->value);
}

Node *add(Node *head, int value)
{
	Node *new_head = calloc(1, sizeof(Node *));
	new_head->value = value;
	if (!head) {
		new_head->next = new_head->prev = new_head;
		return new_head;
	}
	if (head->next == head->prev && head->next == head) { // one element list
		new_head->next = new_head->prev = head;
		head->next = head->prev = new_head;
	} else {
		new_head->next = head;
		new_head->prev = head->prev;
		head->prev->next = new_head;
		head->prev = new_head;
	}
	return new_head;
}

Node *push(Node *head, int value)
{
	Node *new_node = calloc(1, sizeof(Node *));
	new_node->value = value;
	if (!head) {
		new_node->next = new_node->prev = new_node;
		return new_node;
	}
	if (head->next == head->prev && head->next == head ) { // one element list
		new_node->next = new_node->prev = head;
		head->next = head->prev = new_node;
	} else {
		new_node->prev = head->prev;
		new_node->next = head;
		head->prev->next = new_node;
		head->prev = new_node;
	}
	return head;
}

Node *insert(Node *node, int value, int index)
{
	if (!node) return node;
	int i = 0;
	Node *head = node;
	while ( node->next && node->next != head && i < index) {
		node = node->next;
		++i;
	}
	if ( i < index) return head;
	Node *new_node = calloc(1, sizeof(Node *));
	new_node->value = value;
	new_node->prev = node->prev;
	new_node->next = node;
	node->prev->next = new_node;
	node->prev = new_node;
	return head;
}

Node *pop_front(Node *node)
{
	if (!node) return node;
	if (node->next == node->prev && node->next == node) { // one elem list
		free(node);
		return 0;
	}
	Node *new_head = node->next;
	new_head->prev = node->prev;
	node->prev->next = new_head;
	free(node);
	return new_head;
}
	
Node *pop_back(Node *node)
{
	if (!node) return node;
	if (node->next == node->prev && node->next == node) { // one elem list
		free(node);
		return 0;
	}
	Node *me = node->prev;
	me->prev->next = node;
	node->prev = me->prev;
	free(me);
	return node;
}

Node *pop_index(Node *node, int index)
{
	if (!node) return node;
	if (!node->next || !node->prev || (node->prev == node->next && node->next == node)) return node;
	if (index == 0) return pop_front(node);
	int i = 0;
	Node *head = node;
	while (node->next && node->next != head && i < index) {
		node = node->next;
		++i;
	}
	if (i < index) return head;
	Node *me = node;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	return head;
}

int main(void)
{
	Node *head = calloc(1, sizeof(Node *));
	head->next = head->prev = head;
	head = add(head, 1);
	printer(head);
	head = add(head, 2);
	printer(head);
	head = push(head, 3);
	printer(head);
	head = insert(head, 4, 2);
	printer(head);

	head = pop_front(head);
	printer(head);
	head = pop_back(head);
	printer(head);
	head = pop_index(head, 1);
	printer(head);
	head = pop_index(head, 0);
	printer(head);
	head = pop_index(head,0);
	printer(head);

	free_from(head);
}