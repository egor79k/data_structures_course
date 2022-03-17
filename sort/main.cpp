#include <iostream>
#include <string>

#include "sort.h"

namespace sort_test {
    struct Node
    {
        int key;
        std::string data;
    };


    int compareNodes(const Node* n1, const Node* n2)
    {
        return n2->key - n1->key;
    }


    Node** generateArray(const int size)
    {
        Node** nodes = new Node*[size];

        for (int i = 0; i < size; ++i)
        {
            nodes[i] = new Node{rand(), std::to_string(rand())};
        }

        return nodes;
    }


    void deleteArray(Node** nodes, const int size)
    {
        for (int i = 0; i < size; ++i)
        {
            delete nodes[i];
        }

        delete[] nodes;
    }


    bool checkSort(Node** nodes, const int size)
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


    void test_1()
    {
        const int size = 1024;
        Node** nodes = generateArray(size);

        templates::mergeSort<Node>(nodes, size, compareNodes);

        std::cout << "Result: " << checkSort(nodes, size) << std::endl;

        deleteArray(nodes, size);
    }


}; // namespace sort_test


int main()
{
    sort_test::test_1();

    return 0;
}