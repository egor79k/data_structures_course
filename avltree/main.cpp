#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "avltree.h"


namespace avltree_test {
    struct Node
    {
        int key;
        std::string data;

        operator int() const {
            return key;
        }
    };

    int Compare(const Node* n1, const Node* n2)
    {
        return n2->key - n1->key;
    }

    lab618::CMemoryManager<Node> mm(256, true);

    // Генерирует случайный объект
    Node* getRandNode()
    {
        Node* node = mm.newObject();
        node->data = std::to_string(rand());
        node->key = rand();

        return node;
    }

    void test_0(const int at_size=30)
    {
        lab618::CAVLTree<Node, Compare> at;
        std::vector<Node*> nodes(at_size);

        // Добавляем элементы
        for (int i = 0; i < at_size; ++i)
        {
            nodes[i] = mm.newObject();
            nodes[i]->key = rand() % 180;
            printf("Add %d\n", nodes[i]->key);
            fflush(stdout);
            at.add(nodes[i]);
            //at.Dump("tree_full_" + std::to_string(i) + ".png");
        }

        //at.Dump("tree_full.png");

        for (int i = 0; i < at_size; i += 3)
        {
            printf("Remove %d\n", nodes[i]->key);
            fflush(stdout);
            // MAY BE NOT FULL
            assert(at.remove(*nodes[i]) && "Can't remove existing object");
            at.Dump("tree_unfull_" + std::to_string(i) + ".png");
        }

        //at.Dump("tree_unfull.png");
    }

    // Последовательная проверка всех методов
    void test_1(const int at_size=1024)
    {
        lab618::CAVLTree<Node, Compare> at;
        std::vector<Node*> nodes(at_size);

        // Testing add()
        // Добавляем элементы
        for (int i = 0; i < at_size; ++i)
        {
            nodes[i] = getRandNode();
            assert(at.add(nodes[i]) && "Can't add new node");
        }

        //at.Dump("tree.png");

        // Testing update()
        // Обновляем некоторые элементы и проверяем, что они находятся
        for (int i = 0; i < at_size; i += 5)
        {
            Node* node = mm.newObject();
            *node = *(nodes[i]);
            assert(at.update(node) && "Can't update existing object");
            assert(at.find(*nodes[i]) != nullptr && "Can't find existing object");
            assert(at.find(*node) != nullptr && "Can't find existing object");
        }

        // Testing find()
        // Ищем некоторые элементы
        for (int i = 0; i < at_size; i += 4)
        {
            assert(at.find(*nodes[i]) != nullptr && "Can't find existing object");
        }

        // Testing remove()
        // Удаляем некоторые элементы и проверяем, что их нет и их нельзя удалить дважды
        for (int i = 0; i < at_size; i += 3)
        {
            printf("Remove %d\n", i);
            fflush(stdout);
            assert(at.remove(*nodes[i]) && "Can't remove existing object");
            assert(at.find(*nodes[i]) == nullptr && "Find removed object");
            assert(!at.remove(*nodes[i]) && "Object removed twice");
        }

        // Testing clear()
        // Очищаем таблицу и проверяем, ища некоторые элементы
        at.clear();

        for (int i = 0; i < at_size; i += 9)
        {
            assert(at.find(*nodes[i]) == nullptr && "Find object in cleared table");
        }
    }
}; // avltree_test


int main()
{
    srand(42);
    avltree_test::test_0();
    puts("Test 1 ...");
    //avltree_test::test_1();
    puts("OK\nTest 2 ...");
    return 0;
}