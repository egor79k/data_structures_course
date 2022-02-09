#include <iostream>

#include "list.h"

using lab618::CSingleLinkedList;


int main() {
	CSingleLinkedList<int> sl_list;

	int a = 10;

	printf("Size: %d\n", sl_list.getSize());
	sl_list.pushBack(a);
	printf("Size: %d\n", sl_list.getSize());
	sl_list.pushBack(a);
	printf("Size: %d\n", sl_list.getSize());
	sl_list.pushBack(a);
	printf("Size: %d\n", sl_list.getSize());
	//a += 10;
	//sl_list.pushBack(a);
	//a += 10;
	//sl_list.pushBack(a);

	sl_list.popFront();
	printf("Size: %d\n", sl_list.getSize());
	sl_list.popFront();
	printf("Size: %d\n", sl_list.getSize());
	sl_list.popFront();
	printf("Size: %d\n", sl_list.getSize());
	return 0;
}