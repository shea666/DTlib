#ifndef _SMARTPOINT_H_
#define _SMARTPOINT_H_

#include "Object.h"
#include <iostream>

using namespace std;
namespace DTlib
{
template <typename T>
class SmartPointer : public Object
{
	
protected :
	T* m_pointer;
public:
	SmartPointer(T* p = NULL)
	{
		//cout << "111111" <<endl;
		m_pointer = p;	
	}
	
	SmartPointer(const SmartPointer& obj)
	{
		m_pointer = obj.m_pointer;
		//cout << "33333333" <<endl;
		const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;		
	}
	
	SmartPointer<T>& operator= (const SmartPointer<T>& obj)
	{
		if(this != &obj )
		{
			delete m_pointer;
			m_pointer = obj.m_pointer;	
			const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;	
		}
		//cout << "22222222" <<endl;
		return *this;
	}
	
	T* operator-> ()
	{
		return m_pointer;
	}

	T& operator* ()
	{
		return *m_pointer;
	}
	
	bool isNull()
	{
		return (m_pointer == NULL);
	}
	
	T* get()
	{
		return m_pointer;
	}
	
	~SmartPointer()
	{
		delete m_pointer;
	}
};
	
}





#endif