#include <iostream>
#include <string>

#include "hash.h"


struct Node
{
    int key;
    std::string data;
};


unsigned int HashFunc(const Node* n)
{
    return n->key;
}


int Compare(const Node* n1, const Node* n2)
{
    return n1.key - n2.key;
}


int main()
{
    lab618::CHash<Node, HashFunc, Compare> ht(1024, 128);
    return 0;
}