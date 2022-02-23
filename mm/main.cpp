#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "mm.h"


namespace mm_test
{
	struct Node
	{
		int key;
		std::string str;
		// Date date;
	};

	// Последовательное выделение и освобождение памяти
	void test_1(const int max_elements_num=5000)
	{
		lab618::CMemoryManager<Node> mm(256);

		std::vector<Node*> nodes(max_elements_num);

		for (int i = 0; i < max_elements_num; ++i)
		{
			nodes[i] = (mm.newObject());
			assert(nodes[i] != nullptr && "New object is nullptr");
		}

		while (!nodes.empty())
		{
			assert(mm.deleteObject(nodes.back()) && "Can't delete existing object");
			nodes.pop_back();
		}

		try
		{
			mm.clear();
		}
		catch (const lab618::CMemoryManager<Node>::CException& e)
		{
			assert(false && "Clear throws exception after deleting all objects");
		}
	}

	// Выделение и освобождение в случайном порядке
	void test_2(int max_elements_num=5000)
	{
		lab618::CMemoryManager<Node> mm(256, true);

		std::vector<Node*> nodes;

		nodes.push_back(mm.newObject());
		assert(nodes.back() != nullptr && "New object is nullptr");

		while (--max_elements_num)
		{
			switch (rand() % 2)
			{
				case 0:
				{
					nodes.push_back(mm.newObject());
					assert(nodes.back() != nullptr && "New object is nullptr");
					break;
				}

				case 1:
				{
					int id = rand() % nodes.size();
					
					if (nodes[id] != nullptr)
					{
						assert(mm.deleteObject(nodes[id]) && "Can't delete existing object");
						nodes[id] = nullptr;
					}
					else
					{
						assert(!mm.deleteObject(nodes[id]) && "Delete unexisting object");
					}

					break;
				}
			}
		}

		try
		{
			mm.clear();
		}
		catch (const lab618::CMemoryManager<Node>::CException& e)
		{
			assert(false && "Clear throws exception in DeleteElementsOnDestruct mode");
		}
	}
};


int main()
{
	srand(42);

	puts("Test 1");
	mm_test::test_1();
	puts("OK\nTest 2");
	mm_test::test_2();
	puts("OK");

	return 0;
}