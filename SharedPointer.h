#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include <cstdlib>
#include "Pointer.h"
#include "Exception.h"

namespace DTlib
{
template <typename T>
class SharedPointer : public Pointer<T>
{
protected :
    int* m_ref;

    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)
        {
            (*this->m_ref)++;
        }
    }

public :
    SharedPointer(T* p = NULL) : m_ref(NULL)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(std :: malloc(sizeof(int)));
            if(this->m_ref)
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to malloc...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj)
    {
       assign(obj);
    }

    SharedPointer<T> operator =(const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            clear();
            assign(obj);

        }
        return *this;
    }
    void clear()
    {
        T* temp = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = NULL;
        this->m_ref = NULL;

        if(ref)
        {
            (*ref)--;
            if((*ref) == 0)
            {
                free(ref);
                delete temp;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator ==(const SharedPointer<T>& l , const SharedPointer<T>& r )
{
    return (l.get() == r.get());
}

template <typename T>
bool operator !=(const SharedPointer<T>& l , const SharedPointer<T>& r )
{
    return !(l == r);
}

}
#endif // SHAREDPOINTER_H
