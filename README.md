# C_GenericLinkedList
A generic linked list written in C, with list, stack, and queue functionality

I wrote this project because I wanted to gain a better understanding of the C language, as well as things like:
- working with pointers
- generics in C with void*
- function pointers in C
- operation of doubly-linked lists to implement stack/queue functionality

# Documentation

Lists are created using the ```create_list``` function. the function pointers are for how the generic list should print/compare your data type
```
List* create_list(int data_size, void(*print)(void*), int(*compare)(void*, void*));
```

Examples function pointers for an int list:
```
void print(void* data) {
	printf("%d", *(int*)data);
}

int compare(void* data1, void* data2) {
	int d1 = *(int*)data1;
	int d2 = *(int*)data2;
	if (d1 < d2) return -1;
	else if (d1 == d2) return 0;
	else return 1;
}
```

These functions are for using the generic list like a stack
```
void push_data(List* list, void* data);
void* pop_data(List* list);
```

These functions are for using the generic list like a queue
```
void enqueue_data(List* list, void* data);
void* dequeue_data(List* list);
```

Here are some extra functions for list operations. ```delete_data``` deletes the first occurance of a matching data value.
```
void delete_data(List* list, void* data);
void delete_index(List* list, int index);
void free_list(List** list);
void print_list(List* list);
void sort_list(List** list);
```
