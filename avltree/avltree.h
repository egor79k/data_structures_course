#ifndef AVL_HEAD_H_2022_03_24
#define AVL_HEAD_H_2022_03_24

#include <algorithm>

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
            {}
        };

    public:
        CAVLTree(const int defaultBlockSize=256) :
            m_pRoot(nullptr),
            m_Memory(defaultBlockSize, true)
        {}


        virtual ~CAVLTree()
        {
            clear();
        }


        bool add(T* pElement)
        {
            leaf* pTemp = addRec(m_pRoot, pElement);

            if (nullptr == pTemp)
            {
                return false;
            }

            m_pRoot = pTemp;
            return true;

            /*
            if (nullptr == m_pRoot)
            {
                m_pRoot = m_Memory.newObject();
                m_pRoot->pData = pElement;
                return true;
            }

            leaf* pCurr = m_pRoot;

            while (true)
            {
                int cmp_result = Compare(pCurr->pData, pElement);

                if (cmp_result < 0)
                {
                    if (pCurr->pLeft != nullptr)
                    {
                        pCurr = pCurr->pLeft;
                        continue;
                    }

                    pCurr->pLeft = m_Memory.newObject();
                    pCurr->pLeft->pData = pElement;
                    break;
                }

                if (cmp_result > 0)
                {
                    if (pCurr->pRight != nullptr)
                    {
                        pCurr = pCurr->pRight;
                        continue;
                    }

                    pCurr->pRight = m_Memory.newObject();
                    pCurr->pRight->pData = pElement;
                    break;
                }

                return false;
            }

            // BALANCING

            return true;*/
        }


        bool update(T* pElement)
        {
            leaf* pCurr = findLeaf(pElement);

            if (nullptr == pCurr)
            {
                return false;
            }

            pCurr->pData = pElement;
            
            return true;
        }


        T* find(const T& element)
        {
            leaf* pCurr = findLeaf(&element);

            if (nullptr == pCurr)
            {
                return nullptr;
            }

            return pCurr->pData;
        }


        bool remove(const T& element)
        {
            bool isFinded = false;

            m_pRoot = removeRec(m_pRoot, &element, isFinded);

            return isFinded;
        }


        void clear()
        {
            m_Memory.clear();
            m_pRoot = nullptr;
        }


    private:
        leaf* rightRotate(leaf* pCurr)
        {
            leaf* pLeft = pCurr->pLeft;

            if (nullptr == pLeft)
            {
                return pCurr;
            }

            pCurr->pLeft = pLeft->pRight;
            pLeft->pRight = pCurr;

            int cbf = pCurr->balanceFactor;
            int lbf = pLeft->balanceFactor;

            if (lbf <= 0)
            {
                pCurr->balanceFactor = cbf - lbf + 1;
                pLeft->balanceFactor = std::max(lbf - cbf, 1) + cbf + 1;
            }
            else
            {
                ++(pCurr->balanceFactor);
                pLeft->balanceFactor = std::max(-cbf, 1) + cbf + lbf + 1;
            }

            return pLeft;
        }


        leaf* leftRotate(leaf* pCurr)
        {
            leaf* pRight = pCurr->pRight;

            if (nullptr == pRight)
            {
                return pCurr;
            }

            pCurr->pRight = pRight->pLeft;
            pRight->pLeft = pCurr;

            int cbf = pCurr->balanceFactor;
            int lbf = pRight->balanceFactor;

            if (lbf >= 0)
            {
                pCurr->balanceFactor = cbf - lbf - 1;
                pRight->balanceFactor = cbf - std::max(cbf - lbf, 1) - 1;
            }
            else
            {
                --(pCurr->balanceFactor);
                pRight->balanceFactor = cbf + lbf - std::max(cbf, 1) - 1;
            }

            return pRight;
        }


        leaf* balance(leaf* pCurr)
        {
            if (2 == pCurr->balanceFactor)
            {
                if (pCurr->pRight->balanceFactor < 0)
                {
                    pCurr->pRight = rightRotate(pCurr->pRight);
                }

                return leftRotate(pCurr);
            }

            if (-2 == pCurr->balanceFactor)
            {
                if (pCurr->pLeft->balanceFactor > 0)
                {
                    pCurr->pLeft = leftRotate(pCurr->pLeft);
                }

                return rightRotate(pCurr);
            }

            return pCurr;
        }


        leaf* addRec(leaf* pCurr, T* pElement)
        {
            if (nullptr == pCurr)
            {
                pCurr = m_Memory.newObject();
                pCurr->pData = pElement;
                return pCurr;
            }

            int cmp_result = Compare(pCurr->pData, pElement);

            leaf* pChild = nullptr;

            if (cmp_result < 0)
            {
                pChild = addRec(pCurr->pLeft, pElement);

                if (nullptr == pChild)
                {
                    return nullptr;
                }

                pCurr->pLeft = pChild;
                --(pCurr->balanceFactor);
                return balance(pCurr);
            }

            if (cmp_result > 0)
            {
                pChild = addRec(pCurr->pRight, pElement);

                if (nullptr == pChild)
                {
                    return nullptr;
                }

                pCurr->pRight = pChild;
                ++(pCurr->balanceFactor);
                return balance(pCurr);
            }

            return nullptr;
        }


        leaf* removeMin(leaf* pCurr, bool& isRebalanced)
        {
            if (nullptr == pCurr->pLeft)
            {
                isRebalanced = true;
                return pCurr->pRight;
            }

            pCurr->pLeft = removeMin(pCurr->pLeft, isRebalanced);

            if (isRebalanced)
            {
               ++(pCurr->balanceFactor);
            }

            pCurr = balance(pCurr);

            if (0 != pCurr->balanceFactor)
            {
                isRebalanced = false;
            }

            return pCurr;
        }


        leaf* removeRec(leaf* pCurr, const T* pElement, bool& isFinded)
        {
            if (nullptr == pCurr)
            {
                // Не нашли элемент
                isFinded = false;
                return nullptr;
            }

            int cmp_result = Compare(pCurr->pData, pElement);

            leaf* pChild = nullptr;

            if (cmp_result < 0)
            {
                pCurr->pLeft = removeRec(pCurr->pLeft, pElement, isFinded);

                if (!isFinded)
                {
                    return pCurr;
                }

                ++(pCurr->balanceFactor);
                return balance(pCurr);
            }
            
            if (cmp_result > 0)
            {
                pCurr->pRight = removeRec(pCurr->pRight, pElement, isFinded);

                if (!isFinded)
                {
                    return pCurr;
                }

                --(pCurr->balanceFactor);
                return balance(pCurr);
            }

            // Нашли элемент
            isFinded = true;
            leaf* pLeft = pCurr->pLeft;
            leaf* pRight = pCurr->pRight;
            const int bf = pCurr->balanceFactor;
            m_Memory.deleteObject(pCurr);

            if (nullptr == pRight)
            {
                return pLeft;
            }

            // Ищем минимум в правом поддереве
            leaf* pMin = pRight;
            
            while (nullptr != pMin->pLeft)
            {
                pMin = pMin->pLeft;
            }

            bool isRebalanced = false;
            pMin->pRight = removeMin(pRight, isRebalanced);
            pMin->pLeft = pLeft;
            pMin->balanceFactor = bf;

            if (isRebalanced)
            {
                --(pMin->balanceFactor);
            }

            return balance(pMin);
        }


        leaf* findLeaf(const T* pElement)
        {
            if (nullptr == m_pRoot)
            {
                return nullptr;
            }

            leaf* pCurr = m_pRoot;

            while (true)
            {
                int cmp_result = Compare(pCurr->pData, pElement);

                if (cmp_result < 0)
                {
                    if (pCurr->pLeft != nullptr)
                    {
                        pCurr = pCurr->pLeft;
                        continue;
                    }

                    return nullptr;
                }

                if (cmp_result > 0)
                {
                    if (pCurr->pRight != nullptr)
                    {
                        pCurr = pCurr->pRight;
                        continue;
                    }

                    return nullptr;
                }

                return pCurr;
            }
        }


        leaf* m_pRoot;
        CMemoryManager<leaf> m_Memory;
    };

}; // namespace lab618

#endif // #define AVL_HEAD_H_2015_03_31
