#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "hash.h"
#include "mm.h"

namespace hash_test
{
    struct Node
    {
        int key;
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

        return hash + n->key;
    }


    int Compare(const Node* n1, const Node* n2)
    {
        return n2->key - n1->key;
    }


    lab618::CMemoryManager<Node> mm(256, true);

    // Генерирует случайный объект
    Node* getRandNode()
    {
        const char charset[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
        const int chars_num = sizeof(charset);
        const int length = rand() % 20 + 5;
        Node* node = mm.newObject();

        for (int i = 0; i < length; ++i)
        {
            node->data.push_back(charset[rand() % chars_num]);
        }

        node->key = rand();

        return node;
    }

    // Последовательная проверка всех методов
    void test_1(const int ht_size=1024)
    {
        const int elems_num = ht_size * 3;
        lab618::CHash<Node, HashFunc, Compare> ht(ht_size, 128);
        std::vector<Node*> nodes(elems_num);

        // Добавляем элементы
        for (int i = 0; i < elems_num; ++i)
        {
            nodes[i] = getRandNode();
            assert(ht.add(nodes[i]) && "Can't add new node");
        }

        // Testing add()
        // Обновляем некоторые элементы и проверяем, что они находятся
        for (int i = 0; i < elems_num; i += 5)
        {
            Node* node = mm.newObject();
            *node = *(nodes[i]);
            assert(ht.update(node) && "Can't update existing object");
            assert(ht.find(*nodes[i]) != nullptr && "Can't find existing object");
            assert(ht.find(*node) != nullptr && "Can't find existing object");
        }

        // Testing find()
        // Ищем некоторые элементы
        for (int i = 0; i < elems_num; i += 4)
        {
            assert(ht.find(*nodes[i]) != nullptr && "Can't find existing object");
        }

        // Testing remove()
        // Удаляем некоторые элементы и проверяем, что их нет и их нельзя удалить дважды
        for (int i = 0; i < elems_num; i += 3)
        {
            assert(ht.remove(*nodes[i]) && "Can't remove existing object");
            assert(ht.find(*nodes[i]) == nullptr && "Find removed object");
            assert(!ht.remove(*nodes[i]) && "Object removed twice");
        }

        // Testing clear()
        // Очищаем таблицу и проверяем, ища некоторые элементы
        ht.clear();

        for (int i = 0; i < elems_num; i += 9)
        {
            assert(ht.find(*nodes[i]) == nullptr && "Find object in cleared table");
        }
    }

    // Проверка всех методов в случайном порядке
    void test_2(const int ht_size=1024, int iter=10000)
    {
        int elems_num = ht_size * 2;
        lab618::CHash<Node, HashFunc, Compare> ht(ht_size, 128);
        std::vector<Node*> nodes(elems_num);

        // Добавляем элементы
        for (int i = 0; i < elems_num; ++i)
        {
            nodes[i] = getRandNode();
            assert(ht.add(nodes[i]) && "Can't add new node");
        }

        while (iter--)
        {
            switch(rand() % 4)
            {
                // Testing add()
                case 0:
                {
                    Node* node = getRandNode();
                    nodes.push_back(node);
                    assert(ht.add(node) && "Can't add new node");
                    ++elems_num;
                    break;
                }

                // Testing update()
                case 1:
                {
                    int id = rand() % elems_num;
                    Node* node = mm.newObject();
                    *node = *(nodes[id]);
                    assert(ht.update(node) && "Can't update existing object");
                    break;
                }

                // Testing find()
                case 2:
                {
                    int id = rand() % elems_num;
                    assert(ht.find(*nodes[id]) != nullptr && "Can't find existing object");
                    break;
                }

                // Testing remove()
                case 3:
                {
                    int id = rand() % elems_num;
                    assert(ht.remove(*nodes[id]) && "Can't remove existing object");
                    --elems_num;
                    nodes[id] = nodes.back();
                    nodes.resize(elems_num);
                    break;
                }
            }
        }
    }
}; // namespace hash_test


int main()
{
    srand(42);

    puts("Test 1 ...");
    hash_test::test_1();
    puts("OK\nTest 2 ...");
    hash_test::test_2();
    puts("OK\n");

    return 0;
}