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
#include "DTString.h"
#include "Sort.h"

using namespace std;
using namespace DTlib;


int main()
{
    int array[] = {2,435,657,8,5,8,4,98,48,95};
    Sort::Quick(array,10,0);
    for(int i = 0 ;i < 10; i++)
    {
        cout << array[i] <<endl;
    }
    return 0;
}
