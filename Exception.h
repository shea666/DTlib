#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "Object.h"
using namespace std;
namespace DTlib
{
#define THROW_EXCEPTION(e,m)		 (throw e(m,__FILE__,__LINE__))
class Exception : public Object
{
protected :
	char* m_message;
	char* m_location;
	
	void init(const char* message,const char* file,int line);
public :
	Exception(const char* message);
	Exception(const char* file,int line);
	Exception(const char* message,const char* file,int line);
	
	Exception(const Exception &e);
	Exception& operator= (const Exception &e);

	virtual const char* message() const;
	virtual const char* location() const;
	
    virtual ~Exception();
};

class ArithmeticException : public Exception 
{
public :
	ArithmeticException() : Exception(0) { }
	ArithmeticException(const char* message) : Exception(message) {}
	ArithmeticException(const char* file,int line) : Exception(file,line) {}
	ArithmeticException(const char* message,const char* file,int line) : Exception(message,file,line) {}	
	ArithmeticException(const ArithmeticException& e) : Exception(e) {}
	ArithmeticException& operator =(const ArithmeticException& e)
	{
		Exception :: operator = (e);
		return *this;
	}
};

class InvalidOperationException : public Exception
{
public :
	InvalidOperationException() : Exception(0) { }
	InvalidOperationException(const char* message) : Exception(message) {}
	InvalidOperationException(const char* file,int line) : Exception(file,line) {}
	InvalidOperationException(const char* message,const char* file,int line) : Exception(message,file,line) {}	
	InvalidOperationException(const ArithmeticException& e) : Exception(e) {}
	InvalidOperationException& operator =(const ArithmeticException& e)
	{
		Exception :: operator = (e);
		return *this;
	}
};

class InvalidParameterException : public Exception
{
public :
	InvalidParameterException() : Exception(0) { }
	InvalidParameterException(const char* message) : Exception(message) {}
	InvalidParameterException(const char* file,int line) : Exception(file,line) {}
	InvalidParameterException(const char* message,const char* file,int line) : Exception(message,file,line) {}	
	InvalidParameterException(const ArithmeticException& e) : Exception(e) {}
	InvalidParameterException& operator =(const ArithmeticException& e)
	{
		Exception :: operator = (e);
		return *this;
	}
};

class NoEnoughMemoryException : public Exception
{
public :
	NoEnoughMemoryException() : Exception(0) { }
	NoEnoughMemoryException(const char* message) : Exception(message) {}
	NoEnoughMemoryException(const char* file,int line) : Exception(file,line) {}
	NoEnoughMemoryException(const char* message,const char* file,int line) : Exception(message,file,line) {}	
	NoEnoughMemoryException(const ArithmeticException& e) : Exception(e) {}
	NoEnoughMemoryException& operator =(const ArithmeticException& e)
	{
		Exception :: operator = (e);
		return *this;
	}
};

class IndexUutOfBoundsException : public Exception
{
public :
	IndexUutOfBoundsException() : Exception(0) { }
	IndexUutOfBoundsException(const char* message) : Exception(message) {}
	IndexUutOfBoundsException(const char* file,int line) : Exception(file,line) {}
	IndexUutOfBoundsException(const char* message,const char* file,int line) : Exception(message,file,line) {}	
	IndexUutOfBoundsException(const IndexUutOfBoundsException& e) : Exception(e) {}
	IndexUutOfBoundsException& operator =(const IndexUutOfBoundsException& e)
	{
		Exception :: operator = (e);
		return *this;
	}
};

}


#endif
