#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinuxList.h"
#include "Exception.h"

namespace DTlib
{
template <typename T>
class LinkQueue : public Queue<T>
{
protected :
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_head;
    int m_length;
public :

    LinkQueue()
    {
        m_length = 0;
        INIT_LIST_HEAD(&m_head);
    }

    void add(const T& e)
    {
        Node* node = new Node();
        if(node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head , &m_head);
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No memory to add new element...");
        }
    }

    void remove()
    {
        if(m_length > 0)
        {
            list_head* temp = m_head.next;
            list_del(temp);
            m_length--;
            delete list_entry(temp,Node,head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current queue...");
        }
    }

    T front()const
    {
        if(m_length > 0)
        {
            return list_entry(m_head.next,Node,head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current queue...");
        }
    }

    void clear()
    {
        while(m_length > 0)
        {
            remove();
        }
    }

    int length() const
    {
        return m_length;
    }

    ~LinkQueue()
    {
        clear();
    }
};
}
#endif // LINKQUEUE_H
