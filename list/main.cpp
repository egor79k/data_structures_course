#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

#include "list.h"

using lab618::CSingleLinkedList;
using lab618::CDualLinkedList;


class SLListTester
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

		// Fill list with sequence from back
		for (int i = 0; i < size; ++i)
		{
			Map val = {i, std::to_string(i)};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		// Remove all elements from front
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
			switch (rand() % 3)
			{
				case 0:
				{
					Map val = {static_cast<int>(rand()), std::to_string(rand())};
					list.pushBack(val);
					++size;
					break;
				}

				case 1:
				{
					Map val = {static_cast<int>(rand()), std::to_string(rand())};
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
	}

	// Checks operations with iterator
	void test_3(int size = 1000)
	{
		clearAndCheck();

		// Fill list with sequence from back
		for (int i = 0; i < size; ++i)
		{
			Map val = {i, std::to_string(rand())};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		auto it = list.begin();

		// Test list constructors
		CSingleLinkedList<Map>::CIterator it_1(it);
		assert(!(it != it_1) && "Wrong iterator created with copy constructor");

		CSingleLinkedList<Map>::CIterator it_2(it.getLeaf());
		assert(!(it != it_2) && "Wrong iterator constructed from leaf");

		CSingleLinkedList<Map>::CIterator it_3 = it;
		assert(!(it != it_3) && "Wrong iterator copied with assignment");

		// Iterate with increment
		for (int i = 0; i < size; ++i)
		{
			assert(it.isValid() && "Invalid iterator");
			assert((*it).key == i && "Iterator points wrong value");

			++it;
		}

		assert(!it.isValid() && "Iterator valid after list end");
	}

	// Checks erasing
	void test_4(int size = 1000)
	{
		clearAndCheck();

		// Fill list with random sequence from back
		for (int i = 0; i < size; ++i)
		{
			Map val = {static_cast<int>(rand() % 10), std::to_string(rand())};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		auto it = list.begin();

		// Test erasing first element
		list.erase(it);
		++it;
		--size;

		assert(it.isValid() && "Invalid iterator after erase first element");
		assert(!(it != list.begin()) && "Iterator points wrong after erase first element");
		assert(list.getSize() == size && "Wrong size after erase()");
		
		// Erasing elements with key=0
		while (it.isValid())
		{
			if ((*it).key == 0)
			{
				list.erase(it);
				--size;
				
				assert(list.getSize() == size && "Wrong size after erase()");
			}

			++it;
		}
	}
/*
	// Erasing on wrong iterator
	void test_5(int size = 1000)
	{
		clearAndCheck();

		CSingleLinkedList<Map> other_list;

		// Fill lists with random sequence from back
		for (int i = 0; i < size; ++i)
		{
			Map val = {static_cast<int>(rand() % 10), std::to_string(rand())};
			list.pushBack(val);
			other_list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		auto it = list.begin();

		// Move iterator to random position
		for (int i = 0; i < rand() % size; ++i)
		{
			++it;
		}

		bool throws = false;

		// Try to erase elements by wrong iterator
		try
		{
			other_list.erase(it);
		}
		catch (const char* str)
		{
			throws = true;
		}

		assert(throws && "Doesn't throw exception on wrong iterator");
	}
*/
private:
	struct Map
	{
		int key;
		std::string data;
	};

	CSingleLinkedList<Map> list;
};



class DLListTester
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

		// Fill list with sequence from back
		for (int i = 0; i < size; ++i)
		{
			Map val = {i, std::to_string(i)};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		// Remove all elements from front
		for (int i = 0; i < size; ++i)
		{
			assert(list.popFront().key == i && "popFront() returned wrong value");
		}

		assert(list.getSize() == 0 && "Wrong size after popFront()");

		// Fill list with sequence from front
		for (int i = 0; i < size; ++i)
		{
			Map val = {i, std::to_string(i)};
			list.pushFront(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		// Remove all elements from back
		for (int i = 0; i < size; ++i)
		{
			assert(list.popBack().key == i && "popBack() returned wrong value");
		}

		assert(list.getSize() == 0 && "Wrong size after popBack()");
	}

	// Does push and pop in random order
	void test_2(int iter = 1000)
	{
		clearAndCheck();

		int size = 0;

		while (iter--)
		{
			switch (rand() % 4)
			{
				case 0:
				{
					Map val = {static_cast<int>(rand()), std::to_string(rand())};
					list.pushBack(val);
					++size;
					break;
				}

				case 1:
				{
					Map val = {static_cast<int>(rand()), std::to_string(rand())};
					list.pushFront(val);
					++size;
					break;
				}

				case 2:
				{
					if (size > 0)
					{
						list.popBack();
						--size;
					}
					break;
				}

				case 3:
				{
					if (size > 0)
					{
						list.popFront();
						--size;
					}
					break;
				}
			}

			assert(list.getSize() == size && "Wrong size after pop()");
		}
	}

	// Checks operations with iterator
	void test_3(int size = 1000)
	{
		clearAndCheck();

		// Fill list with sequence from back
		for (int i = 0; i < size; ++i)
		{
			Map val = {i, std::to_string(rand())};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		auto it = list.begin();

		// Test list constructors
		CDualLinkedList<Map>::CIterator it_1(it);
		assert(!(it != it_1) && "Wrong iterator created with copy constructor");

		CDualLinkedList<Map>::CIterator it_2(it.getLeaf());
		assert(!(it != it_2) && "Wrong iterator constructed from leaf");

		CDualLinkedList<Map>::CIterator it_3 = it;
		assert(!(it != it_3) && "Wrong iterator copied with assignment");

		// Iterate with increment
		for (int i = 0; i < size; ++i)
		{
			assert(it.isValid() && "Invalid iterator");
			assert((*it).key == i && "Iterator points wrong value");

			++it;
		}

		assert(!it.isValid() && "Iterator valid after list end");

		it = list.end();

		// Iterate with decrement
		for (int i = size - 1; i >= 0; --i)
		{
			assert(it.isValid() && "Invalid iterator");
			assert((*it).key == i && "Iterator points wrong value");

			--it;
		}

		assert(!it.isValid() && "Iterator valid before list begin");
	}

	// Checks erasing
	void test_4(int size = 1000)
	{
		clearAndCheck();

		// Fill list with random sequence from back
		for (int i = 0; i < size; ++i)
		{
			Map val = {static_cast<int>(rand() % 10), std::to_string(rand())};
			list.pushBack(val);
		}

		assert(list.getSize() == size && "Wrong size after pushBack()");

		auto it = list.begin();

		// Test erasing first element
		list.erase(it);
		++it;
		--size;

		assert(it.isValid() && "Invalid iterator after erase first element");
		assert(!(it != list.begin()) && "Iterator points wrong after erase first element");
		assert(list.getSize() == size && "Wrong size after erase()");
		
		// Erasing elements with key=0
		while (it.isValid())
		{
			if ((*it).key == 0)
			{
				list.erase(it);
				--size;
				
				assert(list.getSize() == size && "Wrong size after erase()");
			}

			++it;
		}

		it = list.end();

		// Test erasing last element
		list.eraseAndNext(it);
		--it;
		--size;

		assert(it.isValid() && "Invalid iterator after erase last element");
		assert(!(it != list.end()) && "Iterator points wrong after erase last element");
		assert(list.getSize() == size && "Wrong size after eraseAndNext()");
		
		// Erasing elements with key=1
		while (it.isValid())
		{
			if ((*it).key == 1)
			{
				list.eraseAndNext(it);
				--size;
				
				assert(list.getSize() == size && "Wrong size after eraseAndNext()");
			}

			--it;
		}
	}

private:
	struct Map
	{
		int key;
		std::string data;
	};

	CDualLinkedList<Map> list;
};



int main()
{
	SLListTester sllt;
	
	puts("Testing CSingleLinkedList\nTest 1 ...");
	sllt.test_1();
	puts("OK\nTest 2 ...");
	sllt.test_2();
	puts("OK\nTest 3 ...");
	sllt.test_3();
	puts("OK\nTest 4 ...");
	sllt.test_4();
	puts("OK\n");
	//sllt.test_5();

	DLListTester dllt;
	
	puts("Testing CDualLinkedList\nTest 1 ...");
	dllt.test_1();
	puts("OK\nTest 2 ...");
	dllt.test_2();
	puts("OK\nTest 3 ...");
	dllt.test_3();
	puts("OK\nTest 4 ...");
	dllt.test_4();
	puts("OK\n");

	return 0;
}