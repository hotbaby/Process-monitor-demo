/*************************************************************************
> File Name: hello.cpp
> Author: yy
> Mail: mengyy_linux@163.com
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include <assert.h>

using namespace std;

int main(int, char**)
{
    cout << "hello world." << endl;
    sleep(1);
    assert(0);
    return 0;
}
