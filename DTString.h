#ifndef DTSTRING_H
#define DTSTRING_H

#include "Object.h"

namespace DTlib
{
class String : public Object
{
protected :
    char* m_str;
    int m_length;
    void init(const char* s);
    bool equal(const char* l,const char* s,int len)const;
public :
    String();
    String(char c);
    String(const char* s);
    String(const String& s);
    int length() const;
    const char* str()const;
    bool operator ==(const String& s)const;
    bool operator ==(const char* s)const;
    bool operator !=(const String& s)const;
    bool operator !=(const char* s)const;
    bool operator >(const String& s)const;
    bool operator >(const char* s)const;
    bool operator <(const String& s)const;
    bool operator <(const char* s)const;
    bool operator >=(const String& s)const;
    bool operator >=(const char* s)const;
    bool operator <=(const String& s)const;
    bool operator <=(const char* s)const;
    String operator +(const String& s)const;
    String operator +(const char* s)const;
    String& operator +=(const String& s);
    String& operator +=(const char* s);
    String& operator =(const String& s);
    String& operator =(const char* s);
    String& operator =(const char c);
    char& operator[](int i);
    char operator[](int i)const;
    bool starWith(const char* s)const;
    bool starWith(const String& s)const;
    bool endOf(const char* s)const;
    bool endOf(const String& s)const;
    String& insert(int i , const char* s);
    String& insert(int i , const String& s);
    String& trim();
    ~String();
};
}

#endif // DTSTRING_H
