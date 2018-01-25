#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DTlib
{
template <typename T>
class GTree : public Tree<T>
{
protected :

    LinkQueue<GTreeNode<T>*> m_queue;

    GTreeNode<T>* find(GTreeNode<T>* node , const T& value)const
    {
        GTreeNode<T>* ret = NULL;
        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->chlid.move(0);!node->chlid.end()&&(ret == NULL);node->chlid.next())
                {
                    ret = find(node->chlid.current(),value);
                }
            }
        }
        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node , GTreeNode<T>* obj)const
    {
        GTreeNode<T>* ret = NULL;
        if(node == obj)
        {
            return node;
        }
        else
        {
            if(node != NULL)
            {
                for(node->chlid.move(0);!node->chlid.end()&&(ret == NULL);node->chlid.next())
                {
                    ret = find(node->chlid.current(),obj);
                }
            }
        }
        return ret;
    }

    void free(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->chlid.move(0) ; !node->chlid.end() ; node->chlid.next())
            {
                free(node->chlid.current());
            }
            if(node->flag())
            {
                delete node;
            }
        }
    }

    void remove(GTreeNode<T>* node , GTree<T>*& ret)
    {
        ret = new GTree<T>();
        if(ret == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to malloc...");
        }
        else
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                LinkList<GTreeNode<T>*>& chlid = dynamic_cast<GTreeNode<T>*>(node->parent)->chlid;
                chlid.remove(chlid.find(node));
                node->parent = NULL;
            }
            ret->m_root = node;
        }
    }

    int count(GTreeNode<T>* node)const
    {
        int ret = 0;
        if(node != NULL)
        {
            ret = 1;
            for(node->chlid.move(0);!node->chlid.end();node->chlid.next())
            {
                ret += count(node->chlid.current());
            }
        }
        return ret;
    }

    int height(GTreeNode<T>* node)const
    {
        int ret = 0;
        if(node != NULL)
        {
            for(node->chlid.move(0);!node->chlid.end();node->chlid.next())
            {
                int h = height(node->chlid.current());
                if(ret < h)
                {
                    ret = h;
                }
            }
            ret += 1;
        }
        return ret;
    }

    int degree(GTreeNode<T>* node)const
    {
        int ret = 0;
        if(node != NULL)
        {
            ret = node->chlid.length();
            for(node->chlid.move(0);!node->chlid.end();node->chlid.next())
            {
                int d = degree(node->chlid.current());
                if(ret < d)
                {
                    ret = d;
                }
            }
        }
        return ret;
    }

public :
    GTree()
    {

    }

    bool insert(TreeNode<T>* node)
    {
        bool ret = true;
        if(node != NULL)
        {
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* np = find(node->parent);
                if(np != NULL)
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
                    if(np->chlid.find(n) < 0)
                    {
                        np->chlid.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException,"Node parent cannot find...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Node cannot is NULL...");
        }

        return ret;
    }
    bool insert(const T& value , TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* node = GTreeNode<T>::NewNode();
        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;
            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to malloc...");
        }
        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);
        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException,"Node cannot find...");
        }
        else
        {
            remove(node,ret);
            m_queue.clear();
        }
        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;
        node = find(node);
        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException,"Node is invalid...");
        }
        else
        {
            remove(dynamic_cast<GTreeNode<T>*>(node),ret);
            m_queue.clear();
        }
        return ret;
    }

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(),value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(),dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }
    void clear()
    {
        free(root());
        this->m_root = NULL;
        m_queue.clear();
    }

    bool begin()
    {
        bool ret = (root() != NULL);
        if(ret)
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);
        if(ret)
        {
            GTreeNode<T>* node = m_queue.front();
            m_queue.remove();
            for(node->chlid.move(0);!node->chlid.end();node->chlid.next())
            {
                m_queue.add(node->chlid.current());
            }
        }
        return ret;
    }

    T current()
    {
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
             THROW_EXCEPTION(InvalidOperationException,"No value in current position...");
        }
    }

    ~GTree()
    {
        clear();
    }
};
}
#endif // GTREE_H
