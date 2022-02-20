#include <iostream>

#include "mm.h"


int main()
{
	lab618::CMemoryManager<int> mm(128);
	int* a = mm.newObject();
	return 0;
}