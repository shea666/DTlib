#ifndef _SMARTPOINT_H_
#define _SMARTPOINT_H_

#include "Pointer.h"
#include <iostream>

using namespace std;
namespace DTlib
{
template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
	{

	}
	
	SmartPointer(const SmartPointer& obj)
	{
        this->m_pointer = obj.m_pointer;
		//cout << "33333333" <<endl;
		const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;		
	}
	
	SmartPointer<T>& operator= (const SmartPointer<T>& obj)
	{
		if(this != &obj )
		{
            T* p = this->m_pointer;
            this->m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;	
            delete p;
		}
		//cout << "22222222" <<endl;
		return *this;
	}
	
	~SmartPointer()
	{
        delete this->m_pointer;
	}
};
	
}





#endif
