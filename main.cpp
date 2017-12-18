#include <iostream>
#include "LinkList.h"
#include "SharedPointer.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "LinuxList.h"
#include "DualCircleList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"

using namespace std;
using namespace DTlib;


int main()
{
    LinkQueue<int> queue;
    for(int i = 0 ; i < 5 ; i++)
    {
        queue.add(i);
    }

    while(queue.length() > 0)
    {
        cout << queue.front() <<endl;
        queue.remove();
    }

}
