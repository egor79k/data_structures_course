#ifndef MEMORY_MANAGER_HEAD_H_2022_02_17
#define MEMORY_MANAGER_HEAD_H_2022_02_17

#include <cstring>


namespace lab618
{
    template <class T>
    class CMemoryManager
    {
    private:
        struct block
        {
            // Массив данных блока
            T* pdata;
            // Адрес следующего блока
            block *pnext;
            // Первая свободная ячейка
            int firstFreeIndex;
            // Число заполненных ячеек
            int usedCount;
        };
    public:
        class CException
        {
        public:
            CException()
            {
            }
        };

    public:
        CMemoryManager(int _default_block_size, bool isDeleteElementsOnDestruct = false) :
            m_blkSize(_default_block_size),
            m_pBlocks(nullptr),
            m_pCurrentBlk(nullptr),
            m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct)
        {}

        virtual ~CMemoryManager()
        {
            clear();
        }

        // Получить адрес нового элемента из менеджера
        T* newObject()
        {
            // Если нет блоков, выделяем
            if (m_pCurrentBlk == nullptr)
            {
                m_pCurrentBlk = newBlock();
                return allocateObject();
                //m_pCurrentBlk->firstFreeIndex = *(reinterpret_cast<int*>(m_pCurrentBlk->pdata));
                //m_pCurrentBlk->usedCount++;
                //return m_pCurrentBlk->pdata;
            }

            // Если в текущем блоке есть свободное место, возвращаем его
            if (m_pCurrentBlk->firstFreeIndex != -1)
            {
                return allocateObject();
                //int id = m_pCurrentBlk->firstFreeIndex;
                //m_pCurrentBlk->firstFreeIndex = *(reinterpret_cast<int*>(m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex));
                //m_pCurrentBlk->usedCount++;
                //return m_pCurrentBlk->pdata + id;
            }

            // Иначе ищем место в других блоках
            m_pCurrentBlk = m_pBlocks;

            while (m_pCurrentBlk != nullptr)
            {
                if (m_pCurrentBlk->firstFreeIndex != -1)
                {
                    return allocateObject();
                }

                m_pCurrentBlk = m_pCurrentBlk->pnext;
            }

            // Если не нашли, выделяем новый блок
            m_pCurrentBlk = newBlock();
            return allocateObject();
        }

        // Освободить элемент в менеджере
        bool deleteObject(T* p)
        {
            block *pCurrBlk = m_pBlocks;

            // Ищем элемент по всем блокам
            while (pCurrBlk != nullptr)
            {
                // Если адрес элемента попал в адреса блока, удаляем
                if (pCurrBlk->pdata <= p && p <= (pCurrBlk->pdata + m_blkSize))
                {
                    // Вызываем деструктор объекта и очищаем память
                    p->~T();
                    memset(reinterpret_cast<void*>(p), 0, sizeof(T));

                    // Обновляем данные о свободных ячейках
                    *(reinterpret_cast<int*>(p)) = pCurrBlk->firstFreeIndex;
                    pCurrBlk->firstFreeIndex = p - pCurrBlk->pdata;
                    pCurrBlk->usedCount--;

                    return true;
                }

                pCurrBlk = pCurrBlk->pnext;
            }

            // Иначе такого элемента нет
            return false;
        }

        // Очистка данных, зависит от m_isDeleteElementsOnDestruct
        void clear()
        {
            m_pCurrentBlk = nullptr;

            // Проходим по всем блокам
            while (m_pBlocks != nullptr)
            {
                // Если блок не пуст:
                if (m_pBlocks->usedCount > 0)
                {
                    // В первом режиме кидаем исключение
                    if (m_isDeleteElementsOnDestruct == false)
                    {
                        throw CException();
                    }

                    // Во втором режиме очищаем все неудаленные объекты
                    bool isFree[m_blkSize] = {};

                    int freeIndex = m_pBlocks->firstFreeIndex;

                    while (freeIndex != -1)
                    {
                        isFree[freeIndex] = true;
                        freeIndex = *(reinterpret_cast<int*>(m_pBlocks->pdata + freeIndex));
                    }

                    for (int i = 0; i < m_blkSize; ++i)
                    {
                        if (isFree[i] == false)
                        {
                            (m_pBlocks->pdata + i)->~T();
                        }
                    }
                }

                deleteBlock(m_pBlocks);
            }
        }
    private:

        // Создать новый блок данных. Применяется в newObject
        block* newBlock()
        {
            m_pBlocks = new block{new T[m_blkSize], m_pBlocks, 0, 0};
            
            T* pdata = m_pBlocks->pdata;
            
            for (int i = 0; i < m_blkSize - 1; ++i)
            {
                *(reinterpret_cast<int*>(pdata + i)) = i + 1;
            }

            *(reinterpret_cast<int*>(pdata + m_blkSize - 1)) = -1;

            return m_pBlocks;
        }

        // Освободить память блока данных. Применяется в clear
        void deleteBlock(block* p)
        {
            // Если блок первый в списке, удаляем
            if (p == m_pBlocks)
            {
                m_pBlocks = p->pnext;
                delete[] p->pdata;
                delete p;
                return;
            }

            // Иначе ищем предыдущий блок, чтобы обновить его указатель
            block* pprev = m_pBlocks;

            while (pprev->pnext != p) {
                pprev = pprev->pnext;
            }

            pprev->pnext = p->pnext;

            delete[] p->pdata;
            delete p;
        }

        // Выделить и инициализировать элемент из текущего блока
        T* allocateObject()
        {
            // Берем первую свободную ячейку
            T* pobject = m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex;
            m_pCurrentBlk->firstFreeIndex = *(reinterpret_cast<int*>(m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex));
            m_pCurrentBlk->usedCount++;

            // Очищаем память и конструируем на ней объект
            memset(reinterpret_cast<void*>(pobject), 0, sizeof(T));
            ::new(reinterpret_cast<void*>(pobject)) T;
            
            return pobject;
        }

        // Размер блока
        int m_blkSize;
        // Начало списка блоков
        block* m_pBlocks;
        // Текущий блок
        block *m_pCurrentBlk;
        // Удалять ли элементы при освобождении
        bool m_isDeleteElementsOnDestruct;
    };
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2022_02_17
