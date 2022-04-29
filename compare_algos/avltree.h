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
            bool isRebalanced = false;
            leaf* pTemp = addRec(m_pRoot, pElement, isRebalanced);

            if (nullptr == pTemp)
            {
                return false;
            }

            m_pRoot = pTemp;
            return true;
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
            bool isRebalanced = false;
            leaf* pTemp = removeRec(m_pRoot, &element, isRebalanced);

            if (nullptr == pTemp && !isRebalanced)
            {
                return false;
            }

            m_pRoot = pTemp;
            return true;
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
            int rbf = pRight->balanceFactor;

            if (rbf >= 0)
            {
                pCurr->balanceFactor = cbf - rbf - 1;
                pRight->balanceFactor = cbf - std::max(cbf - rbf, 1) - 1;
            }
            else
            {
                --(pCurr->balanceFactor);
                pRight->balanceFactor = cbf + rbf - std::max(cbf, 1) - 1;
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


        leaf* addRec(leaf* pCurr, T* pElement, bool& isRebalanced)
        {
            if (nullptr == pCurr)
            {
                pCurr = m_Memory.newObject();
                pCurr->pData = pElement;
                isRebalanced = true;
                return pCurr;
            }

            int cmp_result = Compare(pCurr->pData, pElement);

            leaf* pChild = nullptr;

            if (cmp_result < 0)
            {
                pChild = addRec(pCurr->pLeft, pElement, isRebalanced);

                if (nullptr == pChild)
                {
                    return nullptr;
                }

                pCurr->pLeft = pChild;

                if (isRebalanced)
                {
                    --(pCurr->balanceFactor);
                }

                pCurr = balance(pCurr);

                if (0 == pCurr->balanceFactor)
                {
                    isRebalanced = false;
                }

                return pCurr;
            }

            if (cmp_result > 0)
            {
                pChild = addRec(pCurr->pRight, pElement, isRebalanced);

                if (nullptr == pChild)
                {
                    return nullptr;
                }

                pCurr->pRight = pChild;

                if (isRebalanced)
                {
                    ++(pCurr->balanceFactor);
                }

                pCurr = balance(pCurr);

                if (0 == pCurr->balanceFactor)
                {
                    isRebalanced = false;
                }

                return pCurr;
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


        leaf* removeRec(leaf* pCurr, const T* pElement, bool& isRebalanced)
        {
            if (nullptr == pCurr)
            {
                // Не нашли элемент
                isRebalanced = false;
                return nullptr;
            }

            int cmp_result = Compare(pCurr->pData, pElement);

            leaf* pChild = nullptr;

            if (cmp_result < 0)
            {
                pChild = removeRec(pCurr->pLeft, pElement, isRebalanced);

                if (nullptr == pChild && !isRebalanced)
                {
                    return nullptr;
                }

                pCurr->pLeft = pChild;

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
            
            if (cmp_result > 0)
            {
                pChild = removeRec(pCurr->pRight, pElement, isRebalanced);

                if (nullptr == pChild && !isRebalanced)
                {
                    return nullptr;
                }

                pCurr->pRight = pChild;

                if (isRebalanced)
                {
                    --(pCurr->balanceFactor);
                }

                pCurr = balance(pCurr);

                if (0 != pCurr->balanceFactor)
                {
                    isRebalanced = false;
                }

                return pCurr;
            }

            // Нашли элемент
            isRebalanced = true;
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

            pMin->pRight = removeMin(pRight, isRebalanced);
            pMin->pLeft = pLeft;
            pMin->balanceFactor = bf;

            if (isRebalanced)
            {
                --(pMin->balanceFactor);
            }

            pMin = balance(pMin);

            if (0 != pMin->balanceFactor)
            {
                isRebalanced = false;
            }

            return pMin;
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


        void writeLabels (leaf *pCurr, FILE *out)
        {
            fprintf(out, "%d[label = \" {%d | {left\\n%p | balance\\n%d | right\\n%p}} \"]\n", (int)*(pCurr->pData), (int)*(pCurr->pData), pCurr->pLeft, pCurr->balanceFactor, pCurr->pRight);

            if (pCurr->pLeft != NULL)
            {
                writeLabels(pCurr->pLeft, out);
            }

            if (pCurr->pRight != NULL)
            {
                writeLabels(pCurr->pRight, out);
            }

            return;
        }


        void writeConnections (leaf *pCurr, FILE *out)
        {
            if (pCurr->pLeft == NULL && pCurr->pRight == NULL)
            {
                return;
            }

            if (pCurr->pLeft != NULL)
            {
                fprintf(out, "%d->%d [style=\"bold\", color = \"royalblue\"];\n", (int)*(pCurr->pData), (int)*(pCurr->pLeft->pData));
                writeConnections(pCurr->pLeft, out);
            }

            if (pCurr->pRight != NULL)
            {
                fprintf(out, "%d->%d [style=\"bold\", color = \"lawngreen\"];\n", (int)*(pCurr->pData), (int)*(pCurr->pRight->pData));
                writeConnections(pCurr->pRight, out);
            }

            return;
        }


        void dump (std::string pngFile)
        {
            FILE *out = fopen("tree.dot", "w");

            fprintf(out, "digraph {\nnode[shape = record];\n");
            writeLabels(m_pRoot, out);

            if (m_pRoot->pLeft != NULL || m_pRoot->pRight != NULL)
            {
                writeConnections(m_pRoot, out);
            }
            else
            {
                fprintf(out, "%d;\n", (int)*(m_pRoot->pData));
            }

            fprintf(out, "}");
            fclose(out);

            std::string command = "dot tree.dot -T png -o ";
            command += pngFile;
            system (command.data());

            return;
        }

private:
        leaf* m_pRoot;
        CMemoryManager<leaf> m_Memory;
    };

}; // namespace lab618

#endif // #define AVL_HEAD_H_2015_03_31
