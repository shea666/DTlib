#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DTlib
{
enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};
template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
   BTreeNode<T>* left;
   BTreeNode<T>* right;

   BTreeNode()
   {
        left = NULL;
        right = NULL;
   }

   static BTreeNode<T>* NewNode()
   {
       BTreeNode<T>* ret = new BTreeNode<T>();
       if(ret != NULL)
       {
           ret->m_flag = true;
       }
       return ret;
   }
};

}
#endif // BTREENODE_H
