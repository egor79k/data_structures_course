#include "sort.h"

#include "binsearch.h"


namespace lab618
{
    void binSearch(void **ppArray, int length, CompareSortType pCompareFunc)
    {
        mergeSort(ppArray, length, pCompareFunc);
    }
}; // namespace lab618