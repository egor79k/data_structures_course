#include <cassert>
#include <iostream>
#include <string>

#include "sort.h"

namespace sort_test {
    struct Node
    {
        int key;
        std::string data;
    };


    int compareNodes(const Node *n1, const Node *n2)
    {
        return n2->key - n1->key;
    }


    Node **generateArray(const int size)
    {
        Node **nodes = new Node*[size];

        for (int i = 0; i < size; ++i)
        {
            nodes[i] = new Node{rand(), std::to_string(rand())};
        }

        return nodes;
    }


    void deleteArray(Node **nodes, const int size)
    {
        for (int i = 0; i < size; ++i)
        {
            delete nodes[i];
        }

        delete[] nodes;
    }


    bool isSorted(Node** nodes, const int size)
    {
        for (int i = 0; i < size - 1; ++i)
        {
            if (compareNodes(nodes[i], nodes[i + 1]) < 0)
            {
                return false;
            }
        }

        return true;
    }


    void test_1(const int size, int iter=100)
    {
        while(iter--)
        {
            Node **nodes = generateArray(size);

            templates::mergeSort<Node>(nodes, size, compareNodes);

            assert(isSorted(nodes, size) && "Wrong order after sort");

            deleteArray(nodes, size);
        }
    }
}; // namespace sort_test


int main()
{
    srand(42);

    puts("Test 1 ...");
    sort_test::test_1(1024);
    puts("OK\nTest 2 ...");
    sort_test::test_1(4096);
    puts("OK\n");

    return 0;
}