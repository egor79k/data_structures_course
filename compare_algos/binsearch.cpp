#include "sort.h"

#include "binsearch.h"


namespace templates
{
    void binSearch(void **ppArray, int length, CompareSortType pCompareFunc)
    {
        mergeSort(ppArray, length, pCompareFunc);
    }
}; // namespace templates