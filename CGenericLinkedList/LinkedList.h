#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/*
* Structure representing the individual node
*/
typedef struct {
	void* data;
	Node* next, * prev;
}Node;

/*
* Structure representing the list itself
*/
typedef struct {
	Node* head, * tail;
	int count;
	void* max, * min;
	void(*print)(void*);
	int(*compare)(void*, void*);
}List;

/*
* Here our create_list function expects a data size, a function pointer for printing our data, and a function pointer for comparing our data
*/
List* create_list(int data_size, void(*print)(void*), int(*compare)(void*, void*));

/*
* Here are some functions that are only to hep the linked list perform certain fuctions
*/
static Node* create_node(void* data);
static void update_min(List* list);
static void undate_max(List* list);

/*
* These functions allow us to use the list like a stack
*/
void push_data(List* list, void* data);
void* pop_data(List* list);

/*
* These functions allow us to use the list like a queue
*/
void enque_data(List* list, void* data);
void* deque_data(List* list);

/*
* Here are some misc. functions providing more operation on the list
*/
void delete_data(List* list, void* data);
void free_list(List** list);
void print_list(List* list);
void sort_list(List** list);

#endif