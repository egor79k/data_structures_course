#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>


#include "avltree.h"
#include "hash.h"


struct Node
{
    std::string key;
    std::string data;
};


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


lab618::CMemoryManager<Node> mm(256, true);

// Генерирует случайный объект
Node* getRandNode()
{
    Node* node = mm.newObject();

    node->key = getRandString(rand() % 14 + 7);
    node->data = getRandString(rand() % 14 + 7);

    return node;
}


int main()
{
    srand(42);

    return 0;
}