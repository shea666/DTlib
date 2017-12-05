#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include "List.h"
#include "Exception.h"

namespace DTlib
{
template <typename T>
class SeqList : public List<T>
{
protected :
	T* m_array;
	int m_length;
public :
	bool insert(int i,const T& e)
	{
		bool ret = ((0 <= i) && (i <= m_length));
		ret = ret && (m_length < capacity());
		if(ret)
		{
            for(int j = m_length;j > i;j--)
			{
				m_array[j] = m_array[j-1];
			}
			m_array[i] = e;
			m_length += 1;
		}
		return ret;
    }
	
    bool insert(const T& e)
    {
        return insert(m_length,e);
    }

	bool remove(int i)
	{
		bool ret = ((i >= 0) && (i < m_length));
		if(ret)
		{
			for(int j = i;j < m_length - 1;j ++)
			{
				m_array[j] = m_array[j+1];
			}
			m_length -= 1;
		}
		return ret;
	}
	
	bool set(int i,const T& e)
	{
		bool ret = ((i >= 0) && (i < m_length));
		if(ret)
		{
			m_array[i] = e;
		}
		return 0;
	}
	
	bool get(int i,T& e) const
	{
		bool ret = ((i >= 0) && (i < m_length));
		if(ret)
		{
			e = m_array[i];
		}
		return ret;
	}
	
    int find(const T& e)const
    {
        int ret = -1;
        for(int i = 0 ; i < m_length ;i++)
        {
            if(m_array[i] == e)
            {
                ret = i;
                break;
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
		m_length = 0;
		
	}
	
	T& operator [](int i)
	{
		bool ret = ((i >= 0) && (i < m_length));
		if(ret)
		{
			return m_array[i];
		}
		else
		{
			THROW_EXCEPTION(IndexUutOfBoundsException,"Parameter i is invail...");
		}	
	}
	
	T operator [](int i) const
	{
		return (const_cast<SeqList<T>&>(*this))[i];
	}
	
	virtual int capacity() const = 0;
};
	 
}



#endif
