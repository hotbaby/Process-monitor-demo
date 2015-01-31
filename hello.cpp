/*************************************************************************
> File Name: hello.cpp
> Author: yy
> Mail: mengyy_linux@163.com
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include <assert.h>

using namespace std;

int main(int argc, char**argv)
{
    int i = 0;
    for (i=0; i < argc; i++)
        cout << argv[i] << endl;

    cout << "hello world." << endl;
    sleep(1);
    return 0;
}
