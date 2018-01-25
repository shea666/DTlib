#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"


namespace DTlib
{
template <int N , typename V , typename E>
class MatrixGraph : public Graph<V , E>
{
protected :
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;
public :
    MatrixGraph()
    {
        for(int i = 0 ; i < vCount() ; i++)
        {
            m_vertexes[i] = NULL;
            for(int j = 0 ; j < vCount() ; j++)
            {
                m_edges[i][j] = NULL;
            }
        }
        m_eCount = 0;
    }

    V getVertex(int i)
    {
        V ret;
        if(!getVertex(i , ret))
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i...");
        }
        return ret;
    }

    bool getVertex(int i,V& value)
    {
        bool ret = (i >= 0)&&(i < vCount());
        if(ret)
        {
            if(m_vertexes[i] != NULL)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i...");
            }
        }
        return ret;
    }

    bool setVertex(int i,const V& value)
    {
        bool ret = (i >= 0)&&(i < vCount());
        V* data = m_vertexes[i];
        if(ret)
        {
            if(data == NULL)
            {
                data = new V();
            }

            if(data != NULL)
            {
                *data = value;
                m_vertexes[i] = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to new...");
            }
        }
        return ret;
    }

    SharedPointer< Array<int> > getAdjaent(int i)
    {
        DynamicArray<int>* ret = NULL;
        if((i >= 0)&&(i < vCount()))
        {
            int n = 0;
            for(int j = 0 ; j < vCount() ; j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    n++;
                }
            }
            ret = new DynamicArray<int>(n);
            if(ret != NULL)
            {
                for(int j = 0 , k = 0 ; j < vCount() ; j++)
                {
                    if(m_edges[i][j] != NULL)
                    {
                        ret->set(k++,j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to new...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i...");
        }

        return ret;
    }

    E getEdge(int i,int j)
    {
        E ret;
        if(!getEdge(i , j , ret))
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i, j...");
        }

        return ret;
    }

    bool getEdge(int i,int j,E& value)
    {
        bool ret = (i >= 0)&&(i < vCount()&&j >= 0)&&(j < vCount());
        if(ret)
        {
            if(m_edges[i][j] != NULL)
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"No value in this edge...");
            }
        }
        return ret;
    }

    bool isAdjacent(int i , int j)
    {
        return (i>=0)&&(i<vCount())&&(j>=0)&&(j<vCount())&&(m_edges[i][j]!=NULL);
    }

    bool setEdge(int i,int j,const E& value)
    {
        bool ret = (i >= 0)&&(i < vCount()&&j >= 0)&&(j < vCount());
        if(ret)
        {
            E* ne = m_edges[i][j];

            if(ne == NULL)
            {
                ne = new E();
                if(ne != NULL)
                {
                    *ne = value;
                    m_edges[i][j] = ne;
                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to new...");
                }
            }
            else
            {
                *ne = value;
            }
        }

        return ret;
    }

    bool removeEdge(int i,int j)
    {
        bool ret = (i >= 0)&&(i < vCount()&&j >= 0)&&(j < vCount());
        if(ret)
        {
            E* temp = m_edges[i][j];
            m_edges[i][j] = NULL;
            if(temp != NULL)
            {
                m_eCount--;
                delete temp;
            }
        }
        return ret;
    }

    int vCount()
    {
        return N;
    }

    int eCount()
    {
        return m_eCount;
    }

    int OD(int i)
    {
        int ret = 0;
        if((i >= 0)&&(i < vCount()))
        {
            for(int j = 0 ; j < vCount() ; j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i, j...");
        }
        return ret;
    }

    int ID(int i)
    {
        int ret = 0;
        if((i >= 0)&&(i < vCount()))
        {
            for(int j = 0 ; j < vCount() ; j++)
            {
                if(m_edges[j][i] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i, j...");
        }
        return ret;
    }

    ~MatrixGraph()
    {
        for(int i = 0 ; i < vCount() ; i++)
        {
            for(int j = 0 ; j < vCount() ; j++)
            {
                delete m_edges[i][j];
            }
            delete m_vertexes[i];
        }
    }
};

}
#endif // MATRIXGRAPH_H
