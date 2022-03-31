#include "avltree.h"


namespace avltree_test {
    struct Node
    {
        int key;
        std::string data;
    };

    int Compare(const Node* n1, const Node* n2)
    {
        return n2->key - n1->key;
    }

    void test_1()
    {
        lab618::CAVLTree avl_tree();
    }
}; // avltree_test


int main()
{
    return 0;
}