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
            leaf* pcurr = findLeaf(pElement);

            if (nullptr == pcurr)
            {
                return false;
            }

            pcurr->pData = pElement;
            
            return true;
        }

        T* find(const T& pElement)
        {
            leaf* pcurr = findLeaf(&pElement);

            if (nullptr == pcurr)
            {
                return nullptr;
            }

            return pcurr->pData;
        }

        bool remove(const T& element)
        {
            leaf* pcurr = findLeaf(&element);

            if (nullptr == pcurr)
            {
                return false;
            }
        }

        void clear()
        {
            m_Memory.clear();
            m_pRoot = nullptr;
        }

    private:
        leaf* findLeaf(const T* pElement)
        {
            if (nullptr == m_pRoot)
            {
                return nullptr;
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

                    return nullptr;
                }

                if (cmp_result > 0)
                {
                    if (pcurr->pRight != nullptr)
                    {
                        pcurr = pcurr->pRight;
                        continue;
                    }

                    return nullptr;
                }

                return pcurr;
            }
        }

        leaf* m_pRoot;
        CMemoryManager<leaf> m_Memory;
    };

}; // namespace lab618

#endif // #define AVL_HEAD_H_2015_03_31
