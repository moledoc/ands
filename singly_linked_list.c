#include <stdio.h>
#include <stdlib.h>

#define PUSH_TO_EMPTY 0
#define INSERT_TO_NEG_INDEX 0
#define INSERT_TO_EMPTY 0
#define POP_FRONT 0
#define POP_BACK 0
#define POP_INDEX 0
#define POP_NEG_INDEX 0

struct Node {
	int value;
	struct Node *next;
};

struct Node *new_head(int value)
{
	struct Node *head;
	head = malloc(sizeof(struct Node));
	head->value = value;
	return head;
}

// add node to the front
struct Node *add(struct Node *head, int value)
{
	struct Node *new_head = (struct Node *)malloc(sizeof(struct Node));
	new_head->value = value;
	new_head->next = head;	
	return new_head;
}

// push node to the back
struct Node *push(struct Node *node, int value)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->value = value;
	// if provided node is empty, then we create new head
	if (!node) return new_node;

	struct Node *head = node;
	while (node->next) node = node->next;
	node->next = new_node;
	return head;
}

// insert to index
struct Node *insert(struct Node *node, int value, int index)
{
	struct Node *head = node;
	if (index<0) return head;

	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->value = value;
	if (!node) return new_node;

	int i = 1;
	while (node->next && i < index) {
		node = node->next;
		++i;
	}
	
	struct Node *after_new = node->next;
	node->next = new_node;
	new_node->next = after_new;

	return head;
}

// pop_front
struct Node *pop_front(struct Node *node)
{
	if (!node) return node;
	struct Node *new_head = node->next;
	free(node);
	return new_head;
}
// pop_back
struct Node *pop_back(struct Node *node)
{
	if (!node) return node;
	struct Node *head = node;
	while (node->next && node->next->next) node = node->next;
	free(node->next->next);
	node->next = 0x0;
	return head;
}

// pop_index
struct Node *pop_index(struct Node *node, int index)
{
	if (!node || index < 0) return node;
	if (index == 0) {
		struct Node *new_head = node->next;
		free(node);
		return new_head;
	}
	struct Node *head = node;
	int i = 1;
	while (node->next  && i < index) {
		node = node->next;
		++i;
	}
	if (i < index) return head; // if index is greater than the length of the list, do nothing
	struct Node *popping = node->next;
	node->next = node->next->next;
	free(popping);
	return head;
}

void printer(struct Node *node)
{
	while (node) {
		printf(" -> %d", node->value);
		node = node->next;
	}
	printf("\n");
}

void free_all(struct Node *node)
{
	while (node) {
		struct Node *free_me = node;
		node = node->next;
		free(free_me);
	}
}

int main(void)
{
	struct Node *head;
#if PUSH_TO_EMPTY
	head = 0;
#elif INSERT_TO_NEG_INDEX
	head = new_head(0);
	insert(head, 1, -1);
#elif INSERT_TO_EMPTY
	head = 0;
	insert(head, 1, 1);
#else 
	head = new_head(0);
	head = add(head, 1);
#endif

	head = push(head, 2);
	head = push(head, 3);
	head = push(head, 4);
	printer(head);

#if POP_FRONT
	head = pop_front(head);
#elif POP_BACK
	head = pop_back(head);
#elif POP_INDEX
	head = pop_index(head, 7);
#elif POP_NEG_INDEX
	head = pop_index(head, -1);
#endif
	printer(head);

	free_all(head);
}