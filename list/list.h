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
            leaf(T& _data, leaf * _pnext) :
                data(_data),
                pnext(_pnext)
            {}
        };
    public:
        class CIterator
        {
        public:
            CIterator() :
                m_pCurrent(nullptr),
                m_pBegin(nullptr)
            {}

            CIterator(leaf *p) :
                m_pCurrent(p),
                m_pBegin(nullptr)
            {}

            CIterator(const CIterator &src) :
                m_pCurrent(src.m_pCurrent),
                m_pBegin(src.m_pBegin)
            {}

            ~CIterator()
            {
                m_pCurrent = nullptr;
                m_pBegin = nullptr;
            }

            CIterator& operator = (const CIterator&  src)
            {
                m_pCurrent = src.m_pCurrent;
                m_pBegin = src.m_pBegin;
                return *this;
            }

            bool operator != (const CIterator&  it) const
            {
                return m_pCurrent != it.m_pCurrent;
            }

            void operator++()
            {
                if (m_pCurrent != nullptr)
                {
                    m_pCurrent = m_pCurrent->pnext;
                }
                else
                {
                    m_pCurrent = m_pBegin;
                    m_pBegin = nullptr;
                }
            }

            T& getData()
            {
                return m_pCurrent->data;
            }

            T& operator* ()
            {
                return m_pCurrent->data;
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            void setLeaf(leaf* p)
            {
                m_pCurrent = p;
            }

            void setLeafPreBegin(leaf* p)
            {
                m_pBegin = p;
            }

            bool isValid()
            {
                return m_pCurrent != nullptr;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList() :
            m_pBegin(nullptr),
            m_pEnd(nullptr)
        {}

        virtual ~CSingleLinkedList()
        {
            clear();
        }

        void pushBack(T& data)
        {
            if (m_pEnd != nullptr)
            {
                m_pEnd->pnext = new leaf(data, nullptr);
                m_pEnd = m_pEnd->pnext;
            }
            else
            {
                m_pEnd = new leaf(data, nullptr);
                m_pBegin = m_pEnd;
            }
        }

        void pushFront(T& data)
        {
            if (m_pBegin != nullptr)
            {
                m_pBegin = new leaf(data, m_pBegin);
            }
            else
            {
                m_pBegin = new leaf(data, nullptr);
                m_pEnd = m_pBegin;
            }
        }

        T popFront()
        {
            if (m_pBegin == nullptr)
            {
                throw "List is empty!";
            }

            leaf *tmp_ptr = m_pBegin;
            T tmp_data = m_pBegin->data;
            m_pBegin = m_pBegin->pnext;
            delete tmp_ptr;

            return tmp_data;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf *pcurr = it.getLeaf();

            if (pcurr == m_pBegin)
            {
                it.setLeaf(nullptr);
                m_pBegin = pcurr->pnext;
                it.setLeafPreBegin(m_pBegin);

                delete pcurr;
                return;
            }

            leaf *pprev = m_pBegin;

            while (pprev->pnext != pcurr)
            {
                pprev = pprev->pnext;
            }

            pprev->pnext = pcurr->pnext;
            it.setLeaf(pprev);

            delete pcurr;
        }

        int getSize()
        {
            int size = 0;
            leaf *pcurr = m_pBegin;

            while (pcurr != nullptr)
            {
                ++size;
                pcurr = pcurr->pnext;
            }

            return size;
        }

        void clear()
        {
            while (m_pBegin != nullptr)
            {
                leaf *pcurr = m_pBegin;
                m_pBegin = m_pBegin->pnext;
                delete pcurr;
            }

            m_pEnd = nullptr;
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
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
            leaf(T& _data, leaf * _pprev, leaf * _pnext) :
                data(_data),
                pprev(_pprev),
                pnext(_pnext)
            {}
        };
    public:
        class CIterator
        {
        public:
            CIterator() :
                m_pBegin(nullptr),
                m_pCurrent(nullptr),
                m_pEnd(nullptr)
            {}

            CIterator(leaf *p) :
                m_pBegin(nullptr),
                m_pCurrent(p),
                m_pEnd(nullptr)
            {}

            CIterator(const CIterator &src) :
                m_pBegin(src.m_pBegin),
                m_pCurrent(src.m_pCurrent),
                m_pEnd(src.m_pEnd)
            {}

            ~CIterator()
            {
                m_pBegin = nullptr;
                m_pCurrent = nullptr;
                m_pEnd = nullptr;
            }

            CIterator& operator = (const CIterator&  src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                m_pEnd = src.m_pEnd;

                return *this;
            }

            bool operator != (const CIterator&  it) const
            {
                return m_pCurrent != it.m_pCurrent;
            }

            void operator++()
            {
                if (m_pCurrent != nullptr)
                {
                    m_pCurrent = m_pCurrent->pnext;
                }
                else
                {
                    m_pCurrent = m_pBegin;
                    m_pBegin = nullptr;
                }
            }

            void operator--()
            {
                if (m_pCurrent != nullptr)
                {
                    m_pCurrent = m_pCurrent->pprev;
                }
                else
                {
                    m_pCurrent = m_pEnd;
                    m_pEnd = nullptr;
                }
            }

            T& getData()
            {
                return m_pCurrent->data;
            }

            T& operator* ()
            {
                return m_pCurrent->data;
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p)
            {
                m_pCurrent = p;
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
                m_pBegin = p;
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
                m_pEnd = p;
            }

            bool isValid() {
                return m_pCurrent != nullptr;
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

        CDualLinkedList() :
            m_pBegin(nullptr),
            m_pEnd(nullptr)
        {}

        virtual ~CDualLinkedList()
        {
            clear();
        }

        void pushBack(T& data)
        {
            if (m_pEnd != nullptr)
            {
                m_pEnd->pnext = new leaf(data, m_pEnd, nullptr);
                m_pEnd = m_pEnd->pnext;
            }
            else
            {
                m_pEnd = new leaf(data, nullptr, nullptr);
                m_pBegin = m_pEnd;
            }
        }

        T popBack()
        {
            if (m_pEnd == nullptr)
            {
                throw "List is empty!";
            }

            leaf *tmp_ptr = m_pEnd;
            T tmp_data = m_pEnd->data;
            m_pEnd = m_pEnd->pprev;
            
            if (m_pEnd != nullptr)
            {
                m_pEnd->pnext = nullptr;
            }
            else
            {
                m_pBegin = nullptr;
            }

            delete tmp_ptr;

            return tmp_data;
        }

        void pushFront(T& data)
        {
            if (m_pBegin != nullptr)
            {
                m_pBegin->pprev = new leaf(data, nullptr, m_pBegin);
                m_pBegin = m_pBegin->pprev;
            }
            else
            {
                m_pBegin = new leaf(data, nullptr, nullptr);
                m_pEnd = m_pBegin;
            }
        }

        T popFront()
        {
            if (m_pBegin == nullptr)
            {
                throw "List is empty!";
            }

            leaf *tmp_ptr = m_pBegin;
            T tmp_data = m_pBegin->data;
            m_pBegin = m_pBegin->pnext;
            
            if (m_pBegin != nullptr)
            {
                m_pBegin->pprev = nullptr;
            }
            else
            {
                m_pEnd = nullptr;
            }

            delete tmp_ptr;

            return tmp_data;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf *pcurr = it.getLeaf();
            leaf *pnext = pcurr->pnext;
            leaf *pprev = pcurr->pprev;

            if (pnext != nullptr)
            {
                pnext->pprev = pprev;
            }
            else
            {
                m_pEnd = pprev;
            }

            if (pprev != nullptr)
            {
                pprev->pnext = pnext;
                it.setLeaf(pprev);
            }
            else
            {
                it.setLeaf(nullptr);
                m_pBegin = pnext;
                it.setLeafPreBegin(m_pBegin);
            }

            delete pcurr;
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it)
        {
            leaf *pcurr = it.getLeaf();
            leaf *pnext = pcurr->pnext;
            leaf *pprev = pcurr->pprev;

            if (pprev != nullptr)
            {
                pprev->pnext = pnext;
            }
            else
            {
                m_pBegin = pnext;
            }

            if (pnext != nullptr)
            {
                pnext->pprev = pprev;
                it.setLeaf(pnext);
            }
            else
            {
                it.setLeaf(nullptr);
                m_pEnd = pprev;
                it.setLeafPostEnd(m_pEnd);
            }

            delete pcurr;
        }

        int getSize()
        {
            int size = 0;
            leaf *pcurr = m_pBegin;

            while (pcurr != nullptr)
            {
                ++size;
                pcurr = pcurr->pnext;
            }

            return size;
        }

        void clear()
        {
            while (m_pBegin != nullptr)
            {
                leaf *pcurr = m_pBegin;
                m_pBegin = m_pBegin->pnext;
                delete pcurr;
            }

            m_pEnd = nullptr;
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
        }

        CIterator end()
        {
            return CIterator(m_pEnd);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};

#endif //#ifndef TEMPLATES_LIST_2022_02_03
