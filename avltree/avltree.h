#ifndef AVL_HEAD_H_2022_03_24
#define AVL_HEAD_H_2022_03_24

#include "mm.h"

namespace templates
{

    template <class T, int(*Compare)(const T *pElement, const T* pElement2) >
    class CAVLTree
    {
    private:
        struct leaf
        {
            T* pData;
            leaf *pLeft;
            leaf *pRight;
            int balanceFactor;
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
            m_Memory(defaultBlockSize)
        {
        }

        virtual ~CAVLTree()
        {
        }

        bool add(T* pElement)
        {
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
        }

    private:
        leaf* m_pRoot;
        CMemoryManager<leaf> m_Memory;
    };

}; // namespace templates

#endif // #define AVL_HEAD_H_2015_03_31
