#include <algorithm>
#include <iostream>

#include "sort.h"


namespace templates
{
    void mergeSortRecursive(void **ppArray, void **ppTemp, int length, CompareSortType pCompareFunc)
    {
        if (length < 2)
        {
            return;
        }

        // Рекурсивно делим на подзадачи
        const int middle = length / 2;
        mergeSortRecursive(ppArray, ppTemp, middle, pCompareFunc);
        mergeSortRecursive(ppArray + middle, ppTemp, length - middle, pCompareFunc);

        // Объединяем два отсортированных подмассива
        int left_id = 0;
        int right_id = middle;
        int id = 0;

        for (id = 0; right_id < length && left_id < middle; ++id)
        {
            if (pCompareFunc(ppArray[left_id], ppArray[right_id]) > 0)
            {
                // Если текущий элемент левого массива меньше (или во втором
                // массиве не осталось элементов), то следующим кладем его
                ppTemp[id] = ppArray[left_id];
                ++left_id;
            }
            else
            {
                // Иначе кладем текущий элемент из правого массива
                ppTemp[id] = ppArray[right_id];
                ++right_id;
            }
        }

        // Если в левом массиве остались элементы, переносим
        while (left_id < middle) {
            ppTemp[id] = ppArray[left_id];
            ++left_id;
            ++id;
        }

        // Копируем объединенный массив из временной памяти
        for (int i = 0; i < id; ++i)
        {
            ppArray[i] = ppTemp[i];
        }
    }


    void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc)
    {
        void **ppTemp = new void*[length];

        mergeSortRecursive(ppArray, ppTemp, length, pCompareFunc);

        delete[] ppTemp;
    }
}; // namespace templates