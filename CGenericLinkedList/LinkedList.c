#include "LinkedList.h";

List* create_list(int data_size, void(*print)(void*), int(*compare)(void*, void*))
{
	//Here we are malloc-ing memory for our list, and initializing 
	//all of our members to default values.
	List* new_list = (List*)malloc(sizeof(List));
	new_list->data_size = data_size;
	new_list->print = print;
	new_list->compare = compare;
	new_list->count = 0;
	new_list->head = new_list->tail = new_list->min = new_list->max = NULL;
	return new_list;
}

static Node* create_node(int data_size, void* data)
{
	//Here we are malloc-ing the node as well as the data, and initializing
	//all our node members to default values.
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = malloc(data_size);
	memcpy(new_node->data, data, data_size);
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

static void update_min(List* list) {
	//first we check if the list is not allocated
	if (!check_list(list))
		return;

	//then we will iterate through our list
	Node* curr = list->head;
	while (curr) {
		//compare the curr node data with the current minimum value,
		//if the curr data is less, then its the new minimum
		if (list->compare(curr->data, list->min) < 0)
			list->min = curr->data;
	}
}

static void update_max(List* list) {
	//first we check if the list is not allocated
	if (!check_list(list))
		return;

	//then we will iterate through our list
	Node* curr = list->head;
	while (curr) {
		//compare the curr node data with the current maximum value,
		//if the curr data is greater, then its the new maximum
		if (list->compare(curr->data, list->max) > 0)
			list->max = curr->data;
	}
}

static bool check_list(List* list) {
	//check if the list is not allocated:
	//if not, print an error message an return false, else return true
	if (!list) {
		printf("List not allocated, try calling create_list()\n");
		return false;
	}
	return true;
}

void push_data(List* list, void* data) {
	//first we check to see if the list is not allocated
	if (!check_list(list)) {
		return;
	}
	//next create a new node to push
	Node* new_node = create_node(list->data_size, data);
	//check if this will be the first node in the list
	if (list->count == 0) {
		//setting the head and tail to the new node and incrementing count
		list->head = list->tail = new_node;
	}
	else {
		new_node->next = list->head;
		list->head->prev = new_node;
		list->head = new_node;
	}
	list->count++;
}

void* pop_data(List* list) {
	//first we check to see if the list is not allocated
	if (!check_list(list)) {
		return;
	}
	//first we check to see if the list has any nodes
	if (list->count == 0) {
		return NULL;
	}
	else {
		Node* tmp = list->head;
		list->head = list->head->next;
		list->head->prev = NULL;

	}
}

void print_list(List* list) {
	if (!check_list(list)) {
		return;
	}
	Node* curr = list->head;
	printf("List[");
	while (curr) {
		list->print(curr->data);
		if (curr->next) {
			printf(", ");
		}
		curr = curr->next;
	}
	printf("]\n");
}
