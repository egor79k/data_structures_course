#ifndef COMPARE_ALGOS_BINSEARCH_H
#define COMPARE_ALGOS_BINSEARCH_H

namespace lab618
{
    typedef  int (CompareSortType)(const void* pElem1, const void* pElem2);

    template <class T>
    T* binSearch(T** ppArray, int length, T& pObject, int (pCompareFunc)(const T* pElem1, const T* pElem2))
    {
        int left = 0;
        int right = length - 1;

        while (left <= right)
        {
            int median = (right + left) / 2;

            int cmp_res = pCompareFunc(ppArray[median], &pObject);
            
            if (cmp_res < 0)
            {
                // printf("L: l=%d, r=%d, cmp=%d\n", length, start, cmp_res);
                // Go left
                right = median - 1;
            }
            else if (cmp_res > 0)
            {
                // printf("R: l=%d, r=%d, cmp=%d\n", length, start, cmp_res);
                // Go right
                left = median + 1;
            }
            else
            {
                // printf("F: l=%d, r=%d, cmp=%d\n", length, start, cmp_res);
                // Finded
                return ppArray[median];
            }
        }

        return nullptr;
    }
}; // namespace lab618

#endif // #define COMPARE_ALGOS_BINSEARCH_H
