#include <cassert>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

#include "list.h"

using lab618::CSingleLinkedList;


class ListTester
{
public:

	void clearAndCheck()
	{
		list.clear();

		assert(list.getSize() == 0 && "Wrong size after clear()");
	}


	// Pushes back and pops front <size> values
	void test_1(int size = 1000)
	{
		clearAndCheck();

		for (int i = 0; i < size; ++i)
		{
			Map val = {i, std::to_string(i)};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		for (int i = 0; i < size; ++i)
		{
			assert(list.popFront().key == i && "popFront() returned wrong value");
		}

		assert(list.getSize() == 0 && "Wrong size after popFront()");
	}

	// Does push and pop in random order
	void test_2(int iter = 1000)
	{
		clearAndCheck();

		int size = 0;

		while (iter--)
		{
			switch (random() % 3)
			{
				case 0:
				{
					Map val = {static_cast<int>(random()), std::to_string(random())};
					list.pushBack(val);
					++size;
					break;
				}

				case 1:
				{
					Map val = {static_cast<int>(random()), std::to_string(random())};
					list.pushFront(val);
					++size;
					break;
				}

				case 2:
				{
					if (size > 0)
					{
						list.popFront();
						--size;
					}
					break;
				}
			}

			assert(list.getSize() == size && "Wrong size after popFront()");
		}

		//clearAndCheck();
	}

	// Checks operations with iterator
	void test_3(int size = 1000)
	{
		clearAndCheck();

		for (int i = 0; i < size; ++i)
		{
			Map val = {i, std::to_string(random())};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		auto it = list.begin();

		int checkId = random() % size;

		for (int i = 0; i < size; ++i)
		{
			assert(it.isValid() && "Invalid iterator");
			assert((*it).key == i && "Iterator points wrong value");

			if (checkId == i)
			{
				CSingleLinkedList<Map>::CIterator it_1(it);
				assert(!(it != it_1) && "Wrong iterator created with copy constructor");

				CSingleLinkedList<Map>::CIterator it_2(it.getLeaf());
				assert(!(it != it_2) && "Wrong iterator constructed from leaf");

				CSingleLinkedList<Map>::CIterator it_3 = it;
				assert(!(it != it_3) && "Wrong iterator copied with assignment");
			}

			++it;
		}
	}

private:
	struct Map
	{
		int key;
		std::string data;
	};

	CSingleLinkedList<Map> list;
};



int main()
{
	ListTester lt;
	
	puts("Test 1 ...");
	lt.test_1();
	puts("OK\nTest 2 ...");
	lt.test_2();
	puts("OK\nTest 3 ...");
	lt.test_3();
	puts("OK");

	return 0;
}