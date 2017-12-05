#include <iostream>
#include "StaticLinkList.h"

using namespace std;
using namespace DTlib;

int main()
{
    StaticLinkList<int,5> list;

    for(int i=0; i<5; i++)
    {
        list.insert(i,i);
    }


    for(list.move(0); !list.end(); list.next())
    {
        if( list.current() == 3 )
        {
            list.remove(list.find(list.current()));
            cout << list.current() << endl;
        }
    }


    for(list.move(0); !list.end(); list.next())
    {
        cout << list.current() << endl;
    }

    return 0;
}
