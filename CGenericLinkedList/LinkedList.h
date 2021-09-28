#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//both stdio.h and stdlib.h are required to define NULL
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
* Structure representing the individual node
*/
typedef struct node{
	void* data;
	struct node* next, * prev;
}Node;

/*
* Structure representing the list itself
*/
typedef struct list{
	Node* head, * tail;
	int count, data_size;
	void* max, * min;
	void(*print)(void*);
	int(*compare)(void*, void*);
}List;

/*
* Here our create_list function expects a data size, a function pointer for printing our data, and a function pointer for comparing our data
*/
List* create_list(int data_size, void(*print)(void*), int(*compare)(void*, void*));

/*
* Here are some static functions that are only to help the linked list perform certain actions
*/
static Node* create_node(int data_size, void* data);
static void free_node(Node** node);
static void update_min(List* list);
static void update_max(List* list);
static bool check_list(List* list);

/*
* These functions allow us to use the list like a stack
*/
void push_data(List* list, void* data);
void* pop_data(List* list);

/*
* These functions allow us to use the list like a queue
*/
void enqueue_data(List* list, void* data);
void* dequeue_data(List* list);

/*
* Here are some misc. functions providing more operations on the list
*/
void delete_data(List* list, void* data);
void delete_index(List* list, int index);
void free_list(List** list);
void print_list(List* list);
void sort_list(List** list);

#endif