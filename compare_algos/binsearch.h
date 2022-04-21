#ifndef COMPARE_ALGOS_BINSEARCH_H
#define COMPARE_ALGOS_BINSEARCH_H

namespace lab618
{
    typedef  int (CompareSortType)(const void *pElem1, const void *pElem2);

    void binSearch(void **ppArray, int length, CompareSortType pCompareFunc);

    template <class T>
    void binSearch(T **ppArray, int length, int (pCompareFunc)(const T *pElem1, const T *pElem2))
    {
        binSearch(reinterpret_cast<void**>(ppArray), length, (CompareSortType*)pCompareFunc);
    }
}; // namespace lab618

#endif // #define COMPARE_ALGOS_BINSEARCH_H
