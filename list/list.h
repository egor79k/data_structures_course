#ifndef TEMPLATES_LIST_2022_02_03
#define TEMPLATES_LIST_2022_02_03

namespace lab618
{
    template<class T>
    class CSingleLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext;
            leaf(T& _data, leaf * _pnext)
            {
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
                : m_pCurrent(0), m_pBegin(0)
            {
            }

            CIterator(leaf *p)
            {
            }

            CIterator(const CIterator &src)
            {
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
            }

            bool operator != (const CIterator&  it) const
            {
                return true;
            }

            void operator++()
            {
            }

            T& getData()
            {
                return T();
            }

            T& operator* ()
            {
                T tmp;
                return tmp;
            }

            leaf* getLeaf()
            {
                return 0;
            }

            void setLeaf(leaf* p)
            {
            }

            void setLeafPreBegin(leaf* p)
            {
            }

            bool isValid() {
                return false;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList()
        {
        }

        virtual ~CSingleLinkedList()
        {
        }

        void pushBack(T& data)
        {
        }

        void pushFront(T& data)
        {
        }

        T popFront()
        {
            T tmp;
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
        }

        int getSize()
        {
            return 0;
        }

        void clear()
        {
        }

        CIterator begin()
        {
            return CIterator();
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };

    template<class T>
    class CDualLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext, *pprev;
            leaf(T& _data, leaf * _pprev, leaf * _pnext)
            {
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
            {
            }

            CIterator(leaf *p)
            {
            }

            CIterator(const CIterator &src)
            {
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
            }

            bool operator != (const CIterator&  it) const
            {
            }

            void operator++()
            {
            }

            void operator--()
            {
            }

            T& getData()
            {
                T tmp;
                return tmp;
            }

            T& operator* ()
            {
                T tmp;
                return tmp;
            }

            leaf* getLeaf()
            {
                return 0;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p)
            {
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
            }

            bool isValid() {
                return false;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
            //храним конец списка, если мы находимся после конца
            leaf* m_pEnd;
        };

    public:

        CDualLinkedList()
        {
        };

        virtual ~CDualLinkedList()
        {
        };

        void pushBack(T& data)
        {
        }

        T popBack()
        {
            T tmp;
            return tmp;
        }

        void pushFront(T& data)
        {
        }

        T popFront()
        {
            T tmp;
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it)
        {
        }

        int getSize()
        {
            return 0;
        }

        void clear()
        {
        }

        CIterator begin()
        {
            return CIterator();
        }

        CIterator end()
        {
            return CIterator();
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2022_02_03
