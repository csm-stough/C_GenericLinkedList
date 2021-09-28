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

static void free_node(Node** node) {
	free((*node)->data);
	free(*node);
	node = NULL;
}

static void update_min(List* list) {
	//first we check if the list is not allocated
	if (!check_list(list))
		return;

	//then we will iterate through our list
	Node* curr = list->head;
	if (!curr) { list->min = NULL; return; }
	list->min = curr->data;
	while (curr) {
		//compare the curr node data with the current minimum value,
		//if the curr data is less, then its the new minimum
		if (list->compare(curr->data, list->min) < 0)
			list->min = curr->data;
		curr = curr->next;
	}
}

static void update_max(List* list) {
	//first we check if the list is not allocated
	if (!check_list(list))
		return;

	//then we will iterate through our list
	Node* curr = list->head;
	if (!curr) { list->max = NULL; return; }
	list->max = curr->data;
	while (curr) {
		//compare the curr node data with the current maximum value,
		//if the curr data is greater, then its the new maximum
		if (list->compare(curr->data, list->max) > 0)
			list->max = curr->data;
		curr = curr->next;
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
		//no need to call update_max/min, since we already know the max/min here
		list->min = list->max = new_node->data;
	}
	else {
		new_node->next = list->head;
		list->head->prev = new_node;
		list->head = new_node;
		//this is another situation where we dont need to call update_max/min because we know the new max/min here
		if (list->compare(new_node->data, list->max) > 0) {
			list->max = new_node->data;
		}
		else if (list->compare(new_node->data, list->min) < 0) {
			list->min = new_node->data;
		}
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
		//juggling nodes:
		//list->head now points to the old list->head->next
		Node* tmp = list->head;
		list->head = list->head->next;
		//if the new list->head is not null, null the new list->head->prev
		if (list->head)
			list->head->prev = NULL;
		else //list->head == list->tail
			list->tail = NULL;
		//temporary storage for old head data
		void* data = NULL;
		//updating max/min
		if (list->compare(tmp->data, list->max) == 0) {
			update_max(list);
		}
		if (list->compare(tmp->data, list->min) == 0) {
			update_min(list);
		}
		//copying data from old head
		memcpy(&data, tmp->data, list->data_size);
		//freeing the old head
		free_node(&tmp);
		list->count--;
		return &data;
	}
}

void enqueue_data(List* list, void* data) {
	//first we check to see if the list is not allocated
	if (!check_list(list)) {
		return;
	}
	//creating our new node
	Node* new_node = create_node(list->data_size, data);
	//check if the list is empty
	if (list->count == 0) {
		list->head = list->tail = new_node;
		list->min = list->max = new_node->data;
	}
	else {
		//setting the new tail
		list->tail->next = new_node;
		new_node->prev = list->tail;
		list->tail = new_node;
		//updating min/max
		if (list->compare(new_node->data, list->max) > 0) {
			list->max = new_node->data;
		}
		else if (list->compare(new_node->data, list->min) < 0) {
			list->min = new_node->data;
		}
	}
	list->count++;
}

void* dequeue_data(List* list) {
	//For our list dequeue should perform the exact same operation as the pop_data --> no reason to write again
	return pop_data(list);
}

void delete_data(List* list, void* data) {
	//first we check to see if the list is not allocated
	if (!check_list(list)) {
		return;
	}
	//Now iterate through the list, looking for the node to delete
	Node* curr = list->head, * prev = NULL;
	while (curr) {
		if (list->compare(curr->data, data) == 0) {
			//we found the data to delete
			//point the next and prev pointers around the node(if applicable)
			if (prev == NULL) { //curr is the head
				pop_data(list); //removing the head
			}
			else if (!curr->next) { //curr is the tail
				list->tail = list->tail->prev;
				list->tail->next = NULL;
				free_node(&curr);
				list->count--;
			}
			else { //curr is an internal node
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free_node(&curr);
				list->count--;
			}
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	//if we made it here, the data is not in the list
}

void delete_index(List* list, int index) {
	//first we check to see if the list is not allocated
	if (!check_list(list)) {
		return;
	}
	Node* curr = list->head, * prev = NULL;
	int i = 0;
	while (i < index) {
		prev = curr;
		curr = curr->next;
		i++;
		//if curr is null here, the index given is beyond the bounds of the list
		if (!curr) {
			return;
		}
	}
	//at this point curr is the node were deleting
	if (prev == NULL) {
		pop_data(list);
	}
	else if (!curr->next) {
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		free_node(&curr);
		list->count--;
	}
	else {
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		free_node(&curr);
		list->count--;
	}
}

void free_list(List** list) {
	//first we check to see if the list is not allocated
	if (!check_list(*list)) {
		return;
	}
	//while the head of the list isnt null
	while ((*list)->head) {
		//point to the head in a temp variable
		Node* tmp = (*list)->head;
		//head = head.next
		(*list)->head = (*list)->head->next;
		//free the old head
		free_node(&tmp);
	}
	//null out our list ref
	*list = NULL;
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

void sort_list(List** list) {
	//first we check to see if the list is not allocated
	if (!check_list(list)) {
		return;
	}
	//create a new list to hold the sorted values
	List* sorted_list = create_list((*list)->data_size, (*list)->compare, (*list)->print);
	//iterate while there are still values in the unsorted list
	while ((*list)->count > 0) {
		//push the max value of the unsorted list into the sorted list
		push_data(sorted_list, (*list)->max);
		//then delete that value from the unsorted list
		delete_data(*list, (*list)->max);
	}
	//free up the unsorted list
	free_list(list);
	//reassign the pointer to our list to the new sorted list
	*list = sorted_list;
}
