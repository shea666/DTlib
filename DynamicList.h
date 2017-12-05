#ifndef _DYNAMICLIST_H
#define _DYNAMICLIST_H
#include "SeqList.h"

namespace DTlib
{
template <typename T>
class DynamicList : public SeqList<T>
{
protected :
    int m_capacity;
public :
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];
        if(this->m_array != NULL)
        {
            this->m_capacity = capacity;
            this->m_length = 0;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to creat DynamicList...");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    void resize(int capacity)
    {
        if(capacity != m_capacity)
        {
            T* array = new T[capacity];
            if(array != NULL)
            {
                int length = capacity > this->m_length ? this->m_length : capacity;
                for(int i = 0;i < length;i++)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;
                this->m_array = array;
                this->m_length = length;
                m_capacity = capacity;
                delete []temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to resize DynamicList...");
            }
        }
    }

    ~DynamicList()
    {
        delete []this->m_array;
    }
};
}

#endif // DYNAMICLIST_H
