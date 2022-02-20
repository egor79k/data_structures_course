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
            return false;
        }

        // Очистка данных, зависит от m_isDeleteElementsOnDestruct
        void clear()
        {
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
        void deleteBlock(block *p)
        {
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
