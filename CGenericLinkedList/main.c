#include "LinkedList.h";

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

int main(int argc, char** argv) {
	//creating a list
	List* list = create_list(sizeof(int), &print, &compare);
	
	//pushing data to the list
	for (int i = 0; i < 10; i++) {
		push_data(list, &i);
	}

	//print the list
	print_list(list);

	return 0;
}