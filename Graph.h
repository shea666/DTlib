#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"

using namespace std;

namespace DTlib
{
template<typename E>
struct Edge : public Object
{
    int b;
    int e;
    E data;

    Edge(int i = -1 , int j = -1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j , const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator == (const Edge& obj)
    {
        return (b == obj.b)&&(e == obj.e);
    }

    bool operator != (const Edge& obj)
    {
        return !(*this == obj);
    }
};

template <typename V , typename E>
class Graph : public Object
{
protected :
    template<typename T>
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());
        if(ret != NULL)
        {
            cout <<"queue.length() :"<< queue.length()<<endl;
            cout <<"ret->length() :"<< ret->length()<<endl;
            for(int i = 0 ; i < ret->length() ; i++,queue.remove())
            {
                ret->set(i,queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to new...");
        }
        return ret;
    }

public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i,V& value) = 0;
    virtual bool setVertex(int i,const V& value) = 0;
    virtual SharedPointer< Array<int> > getAdjaent(int) = 0;
    virtual bool isAdjacent(int i , int j) = 0;
    virtual E getEdge(int i,int j) = 0;
    virtual bool getEdge(int i,int j,E& value) = 0;
    virtual bool setEdge(int i,int j,const E& value) = 0;
    virtual bool removeEdge(int i,int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;

    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    bool asUndirected()
    {
        bool ret = true;

        for(int i = 0 ; i < vCount() ; i++)
        {
            for(int j = 0 ; j < vCount() ; j++)
            {
                if (isAdjacent(i, j))
                {
                    ret = ret&&isAdjacent(i,j)&&isAdjacent(j,i)&&(getEdge(i,j)==getEdge(j,i));
                }
            }
        }

        return ret;
    }

    SharedPointer<Array<int> > BFS(int i)
    {
        DynamicArray<int>* ret = NULL;
        if((i >= 0)&&(i < vCount()))
        {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for(int j = 0 ; j < visited.length() ; j++)
            {
                visited[j] = false;
            }

            q.add(i);

            while(q.length() > 0)
            {
                int v = q.front();
                q.remove();
                if(!visited[v])
                {
                    SharedPointer<Array<int> > aj = getAdjaent(v);

                    for(int j = 0 ; j < aj->length() ; j++)
                    {
                        q.add((*aj)[j]);
                    }

                    r.add(v);
                    visited[v] = true;
                }
            }
            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i...");
        }

        return ret;
    }

    SharedPointer<Array<int> > DFS(int i)
    {
        DynamicArray<int>* ret = NULL;
        if((i >= 0)&&(i < vCount()))
        {
            LinkStack<int> s;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for(int j = 0 ; j < visited.length() ; j++)
            {
                visited[j] = false;
            }

            s.push(i);

            while(s.size() > 0)
            {
                int v = s.top();
                s.pop();
                if(!visited[v])
                {
                    SharedPointer<Array<int> > aj = getAdjaent(v);

                    for(int j = 0 ; j < aj->length() ; j++)
                    {
                        s.push((*aj)[j]);
                    }
                    /*
                    for (int j=aj->length()-1; j>=0; j--)
                    {
                        s.push((*aj)[j]);
                    }
                    */
                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Invalid parameter i...");
        }

        return ret;
    }

    SharedPointer<Array<Edge<E> > > prim(const E& LIMIT , const bool MINIMUM = true)
    {
        LinkQueue<Edge<E> > ret;
        if(asUndirected())
        {
            DynamicArray<int> adjVex(vCount());
            DynamicArray<bool> mark(vCount());
            DynamicArray<E> cost(vCount());
            SharedPointer<Array<int> > aj = NULL;
            bool end = false;
            int v = 0;
            for(int i = 0 ; i < vCount() ; i++)
            {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT;
            }

            mark[v] = true;
            aj = getAdjaent(v);
            for(int j = 0 ; j < aj->length() ; j++)
            {
                cost[(*aj)[j]] = getEdge(v,(*aj)[j]);
                adjVex[(*aj)[j]] = v;
            }

            for(int i = 0;(i < vCount())&&(!end) ;i++)
            {
                E m = LIMIT;
                int k = -1;
                for(int j = 0 ; j < vCount() ; j++)
                {
                    if((!mark[j])&&(MINIMUM ? (cost[j] < m) : (cost[j] > m)))
                    {
                        m = cost[j];
                        k = j;
                    }
                }

                end = (k == -1);
                if(!end)
                {
                    ret.add(Edge<E>(adjVex[k],k,getEdge(adjVex[k],k)));
                    mark[k] = true;
                    aj = getAdjaent(k);

                    for(int j = 0 ; j < aj->length() ; j++)
                    {
                        if((!mark[(*aj)[j]])&&(MINIMUM ? (getEdge(k,(*aj)[j])<cost[(*aj)[j]]) : (getEdge(k,(*aj)[j])>cost[(*aj)[j]])))
                        {
                            cost[(*aj)[j]] = getEdge(k,(*aj)[j]);
                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"Prim operator is for undirected...");
        }

        if(ret.length() != (vCount() - 1))
        {
            THROW_EXCEPTION(InvalidOperationException,"No enough edge for prim operator...");
        }
        return toArray(ret);
    }

};

}

#endif // GRAPH_H
