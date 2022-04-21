#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>


#include "avltree.h"
#include "hash.h"


namespace experiment
{
private:
    struct Node
    {
        std::string key;
        std::string data;
    };


    unsigned int HashFunc(const Node* n)
    {
        const int p = 62;
        int p_pow = 1;
        unsigned int hash = 0;

        for (auto& ch : n->data)
        {
            hash += ch * p_pow;
            p_pow *= p;
        }

        return hash;
    }


    int Compare(const Node* n1, const Node* n2)
    {
        return strcmp(n1->key.data(), n2->key.data());
    }


    std::string getRandString(const int length)
    {
        const char charset[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
        const int chars_num = sizeof(charset);
        std::string str;

        for (int i = 0; i < length; ++i)
        {
            str.push_back(charset[rand() % chars_num]);
        }

        return str;
    }

    const int block_size = 1024;
    lab618::CMemoryManager<Node> mm(block_size, true);

    // Генерирует случайный объект
    Node* getRandNode()
    {
        Node* node = mm.newObject();

        node->key = getRandString(rand() % 14 + 7);
        node->data = getRandString(rand() % 14 + 7);

        return node;
    }

    void measure(const int size)
    {
        Node** nodes = new Node*[size];

        for (int i = 0; i < size; ++i)
        {
            nodes[i] = getRandNode();
        }

        lab618::CHash<Node, HashFunc, Compare> ht(size / 2, size / 20);
        lab618::CAVLTree<Node, Compare> at;

        
    }
}; // namespace experiment


int main()
{
    srand(42);

    return 0;
}