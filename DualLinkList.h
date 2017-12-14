#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTlib
{
template <typename T>
class DualLinkList : public List<T>
{
protected :
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;
    }m_header;

    int m_length;
    Node* m_current;
    int m_step;

    Node* position(int i)const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int p = 0 ; p < i ; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* creat()
    {
        return new Node();
    }

    virtual void destroy(Node* p)
    {
        delete(p);
    }

public :
    DualLinkList()
    {
        m_header.next = NULL;
        m_header.pre = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    bool insert(const T& e)
    {
        return insert(m_length,e);
    }

    bool insert(int i,const T& e)
    {
        bool ret = (i >= 0 && i <= m_length);
        if(ret)
        {
            Node* node = creat();
            if(node != NULL)
            {
                Node* current = position(i);
                Node* next = current->next;
                node->value = e;
                node->next = next;
                current->next = node;

                if(current != reinterpret_cast<Node*>(&m_header))
                {
                    node->pre = current;
                }
                else
                {
                    node->pre = NULL;
                }

                if(next != NULL)
                {
                    next->pre = node;
                }

                m_length++;
            }
            else
            {
                 THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to insert new...");
            }
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = (i >= 0 && i < m_length);
        if(ret)
        {
            Node* current = position(i);
            Node* temp = current->next;
            Node* next = temp->next;
            if(m_current == temp) //游标指向待删元素
            {
                m_current = next;
            }
            current->next = next;
            if(next != NULL)
            {
                next->pre = temp->pre;
            }
            m_length--;
            destroy(temp);
        }

        return ret;
    }

    bool set(int i,const T& e)
    {
        bool ret = (i >= 0 && i < m_length);
        if(ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    bool get(int i,T& e) const
    {
        bool ret = (i >= 0 && i < m_length);
        if(ret)
        {
            e = position(i)->next->value;
        }

        return ret;
    }

    virtual T get(int i) const
    {
        T ret;
        if( get(i,ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i...");
        }
        return ret;
    }

    int find(const T& e)const
    {
        int ret = -1;
        int i = 0;
        Node* node = m_header.next;
        while(node)
        {
            if(node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }

        return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        while(m_length > 0)
        {
            remove(0);
        }
    }

    virtual bool move(int i,int step = 1)
    {
        bool ret = (i >= 0 && i < m_length && step > 0);
        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
    }

    virtual bool end()
    {
        return (m_current == NULL);
    }

    virtual T current()
    {
        if(!end())
        {
           return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No value in current position...");
        }
    }

    virtual bool next()
    {
        int i = 0;
        while(i < m_step && (!end()))
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    virtual bool pre()
    {
        int i = 0;
        while(i < m_step && (!end()))
        {
            m_current = m_current->pre;
            i++;
        }

        return (i == m_step);
    }



    ~DualLinkList()
    {
        clear();
    }


};

}
#endif // DUALLINKLIST_H
