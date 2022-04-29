#include <cassert>
#include <chrono>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "avltree.h"
#include "hash.h"
#include "binsearch.h"
#include "sort.h"


class Experiment
{
public:
    Experiment(const int size_, const int block_size) :
        size(size_),
        at(block_size),
        ht(size_ / 2, block_size),
        mm(block_size, true),
        nodes(new Node*[size_])
    {
        for (int i = 0; i < size; ++i)
        {
            nodes[i] = getRandNode(mm.newObject());
        }
    }


    void measureFilling(std::ostream &ostr)
    {
        ostr << size << ",FL,";
        // AVLTree
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; ++i)
        {
            at.add(nodes[i]);
        }

        std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // HashTable
        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; ++i)
        {
            ht.add(nodes[i]);
        }

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // BinarySearch
        start = std::chrono::high_resolution_clock::now();

        lab618::mergeSort<Node>(nodes, size, Compare);

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << '\n';
    }


    void measureFindingKnown(std::ostream &ostr)
    {
        ostr << size << ",FK,";

        // AVLTree
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; ++i)
        {
            at.find(*nodes[i]);
        }

        std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // HashTable
        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; ++i)
        {
            ht.find(*nodes[i]);
        }

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        lab618::mergeSort<Node>(nodes, size, Compare);

        // BinarySearch
        start = std::chrono::high_resolution_clock::now();


        for (int i = 0; i < size; ++i)
        {
            lab618::binSearch<Node>(nodes, size, *nodes[i], Compare);
        }

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << '\n';
    }


    void measureFindingUnknown(std::ostream &ostr)
    {
        ostr << size << ",FU,";

        const int size_2 = 2 * size;
        Node** unk_nodes = new Node*[size_2];

        for (int i = 0; i < size_2; ++i)
        {
            unk_nodes[i] = getRandNode(mm.newObject());
        }

        // AVLTree
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size_2; ++i)
        {
            at.find(*unk_nodes[i]);
        }

        std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // HashTable
        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size_2; ++i)
        {
            ht.find(*unk_nodes[i]);
        }

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // BinarySearch
        start = std::chrono::high_resolution_clock::now();


        for (int i = 0; i < size_2; ++i)
        {
            lab618::binSearch<Node>(nodes, size, *unk_nodes[i], Compare);
        }

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << '\n';

        delete[] unk_nodes;
    }


    void measureClearingFull(std::ostream &ostr)
    {
        ostr << size << ",CF,";

        // AVLTree
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        at.clear();

        std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // HashTable
        start = std::chrono::high_resolution_clock::now();

        ht.clear();

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // BinarySearch
        Node** old_nodes = new Node*[size];

        for (int i = 0; i < size; ++i)
        {
            old_nodes[i] = nodes[i];
        }

        start = std::chrono::high_resolution_clock::now();

        delete[] nodes;

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << '\n';

        nodes = old_nodes;
    }


    void measureClearingElementwise(std::ostream &ostr)
    {
        ostr << size << ",CE,";

        for (int i = 0; i < size; ++i)
        {
            at.add(nodes[i]);
            ht.add(nodes[i]);
        }

        // AVLTree
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; ++i)
        {
            at.remove(*nodes[i]);
        }

        std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << ',';

        // HashTable
        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; ++i)
        {
            ht.remove(*nodes[i]);
        }

        stop = std::chrono::high_resolution_clock::now();

        ostr << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << '\n';
    }


private:
    struct Node
    {
        std::string key;
        std::string data;
    };


    static unsigned int HashFunc(const Node* n)
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


    static int Compare(const Node* n1, const Node* n2)
    {
        return strcmp(n2->key.data(), n1->key.data());
    }


    std::string getRandString(const int length)
    {
        const char charset[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
        const int chars_num = sizeof(charset) - 1;
        std::string str;

        for (int i = 0; i < length; ++i)
        {
            str.push_back(charset[rand() % chars_num]);
        }

        return str;
    }

    // Генерирует случайный объект
    Node* getRandNode(Node* node)
    {
        node->key = getRandString(rand() % 14 + 7);
        node->data = getRandString(rand() % 14 + 7);

        return node;
    }


    const int size;
    lab618::CMemoryManager<Node> mm;
    lab618::CHash<Node, HashFunc, Compare> ht;
    lab618::CAVLTree<Node, Compare> at;
    Node** nodes = nullptr;
};


int main()
{   
    srand(42);
    
    std::ofstream results_csv("experiment.csv", std::ios::app);

    if (!results_csv.is_open()) {
        perror("Can't open file");
        return 1;
    }

    const int min_size = 10000;
    const int max_size = 1000000;
    const int step = (max_size - min_size) / 20;

    for (int exp_size = min_size; exp_size <= max_size; exp_size += step)
    {
        std::cout << "Size: " << exp_size << std::endl;
        Experiment exp(exp_size, 4096);
        exp.measureFilling(results_csv);
        exp.measureFindingKnown(results_csv);
        exp.measureFindingUnknown(results_csv);
        exp.measureClearingFull(results_csv);
        exp.measureClearingElementwise(results_csv);
    }

    results_csv.close();

    return 0;
}