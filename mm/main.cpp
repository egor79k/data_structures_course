#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "mm.h"


namespace mm_test
{
	struct Node
	{
		int key = 1;
		std::string str = "empty";
		std::string date = "";
	};

	// Последовательное выделение и освобождение памяти
	void test_1(const int max_elements_num=5000, const int block_size=256)
	{
		lab618::CMemoryManager<Node> mm(block_size);

		std::vector<Node*> nodes(max_elements_num);

		for (int i = 0; i < max_elements_num; ++i)
		{
			nodes[i] = (mm.newObject());
			assert(nodes[i] != nullptr && "New object is nullptr");
			assert(1 == nodes[i]->key && "empty" == nodes[i]->str && "Object not constructed");
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
	void test_2(int max_elements_num=5000, const int block_size=256)
	{
		lab618::CMemoryManager<Node> mm(block_size, true);

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

	// Другие случаи
	void test_3(const int block_size=128)
	{
		lab618::CMemoryManager<Node> mm1(block_size, true);
		lab618::CMemoryManager<Node> mm2(block_size);

		Node *n1 = mm1.newObject();
		Node *n2 = mm2.newObject();

		assert(n1 != nullptr && "New object is nullptr");
		assert(n2 != nullptr && "New object is nullptr");

		assert(!mm1.deleteObject(n2) && "Delete object from other manager");
		assert(!mm2.deleteObject(n1) && "Delete object from other manager");

		assert(mm1.deleteObject(n1) && "Can't delete existing object");
		assert(mm2.deleteObject(n2) && "Can't delete existing object");

		assert(!mm1.deleteObject(n1) && "Delete unexisting object");
		assert(!mm2.deleteObject(n2) && "Delete unexisting object");

		std::vector<Node*> nodes(block_size);

		// Заполняем ровно один блок
		for (int i = 0; i < block_size; ++i)
		{
			nodes[i] = (mm1.newObject());
			assert(nodes[i] != nullptr && "New object is nullptr");
		}

		Node *rand_obj = nodes[rand() % block_size];

		assert(mm1.deleteObject(rand_obj) && "Can't delete existing object");

		assert(mm1.newObject() == rand_obj && "Wrong allocation behaviour");
	}
};


int main()
{
	srand(42);

	puts("Test 1");
	mm_test::test_1();
	puts("OK\nTest 2");
	mm_test::test_2();
	puts("OK\nTest 3");
	mm_test::test_3();
	puts("OK");

	return 0;
}