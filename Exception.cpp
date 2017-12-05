#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "Exception.h"


using namespace std;

namespace DTlib
{
	
void Exception :: init(const char* message,const char* file,int line)
{
    //m_message = strdup(message);
    m_message = message ? strdup(message) : NULL;
	if(file != NULL)
	{
		char sl[16] = {0};
		snprintf(sl,sizeof(sl),"%d",line);  //itoa(line,sl,10);
		m_location = static_cast<char*>(malloc(strlen(sl) + strlen(file) + 2));
		if(m_location != NULL)
		{
			m_location = strcpy(m_location,file);
			m_location = strcat(m_location,":");
			m_location = strcat(m_location,sl);
		}		
	}
	else
	{
		m_location = NULL;
		m_location = NULL;
	}
}

Exception :: Exception(const char* message)
{
	init(message,NULL,0);
}

Exception ::Exception(const char* file,int line)
{
	init(NULL,file,line);
}

Exception :: Exception(const char* message,const char* file,int line)
{
	init(message,file,line);
}
	
Exception :: Exception(const Exception &e)
{
	m_location = strdup(e.m_location);
	m_message = strdup(e.m_message);
}

Exception& Exception :: operator= (const Exception &e)
{
	if(this != &e)
	{
		free(m_location);
		free(m_message);
		
		m_location = strdup(e.m_location);
		m_message = strdup(e.m_message);
	}
	
	return *this;
}

const char* Exception :: message() const
{
	return m_message;
}

const char* Exception :: location() const
{
	return m_location;
}

Exception :: ~Exception()
{
	free(m_message);
	free(m_location);
}

}
