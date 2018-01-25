#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTlib
{
template <typename T>
class TreeNode : public Object
{
public :
    T value;
    TreeNode<T>* parent; 
    bool m_flag;
    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator=(const TreeNode<T>&);
    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }
    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T> :: ~TreeNode()
{

}

}
#endif // TREENODE_H
