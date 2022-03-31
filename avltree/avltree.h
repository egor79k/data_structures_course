#ifndef AVL_HEAD_H_2022_03_24
#define AVL_HEAD_H_2022_03_24

#include "mm.h"

namespace lab618
{

    template <class T, int(*Compare)(const T *pElement, const T* pElement2) >
    class CAVLTree
    {
    private:
        struct leaf
        {
            T* pData = nullptr;
            leaf *pLeft = nullptr;
            leaf *pRight = nullptr;
            int balanceFactor = 0;
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
        CAVLTree(const int defaultBlockSize=256) :
            m_pRoot(nullptr),
            m_Memory(defaultBlockSize, true)
        {
        }

        virtual ~CAVLTree()
        {
            clear();
        }

        bool add(T* pElement)
        {
            if (nullptr == m_pRoot)
            {
                m_pRoot = m_Memory.newObject();
                m_pRoot->pData = pElement;
                return true;
            }

            leaf* pcurr = m_pRoot;

            while (true)
            {
                int cmp_result = Compare(pcurr->pData, pElement);

                if (cmp_result < 0)
                {
                    if (pcurr->pLeft != nullptr)
                    {
                        pcurr = pcurr->pLeft;
                        continue;
                    }

                    pcurr->pLeft = m_Memory.newObject();
                    pcurr->pLeft->pData = pElement;
                    break;
                }

                if (cmp_result > 0)
                {
                    if (pcurr->pRight != nullptr)
                    {
                        pcurr = pcurr->pRight;
                        continue;
                    }

                    pcurr->pRight = m_Memory.newObject();
                    pcurr->pRight->pData = pElement;
                    break;
                }

                return false;
            }

            // BALANCING

            return true;
        }

        bool update(T* pElement)
        {
        }
      
        T* find(const T& pElement)
        {
        }

        bool remove(const T& element)
        {
        }

        void clear()
        {
            m_Memory.clear();
            m_pRoot = nullptr;
        }

    private:
        leaf* m_pRoot;
        CMemoryManager<leaf> m_Memory;
    };

}; // namespace templates

#endif // #define AVL_HEAD_H_2015_03_31
