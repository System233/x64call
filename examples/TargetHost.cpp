/**
 * Copyright (c) 2021 github.com/System233
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <Windows.h>
#include <iostream>
DWORD test(LPVOID*lp){
    MessageBoxA(NULL,"TEST FUNC","TEST",MB_OK);
    return 0;
}
int main(int argc, char const *argv[])
{
    std::cout<<"PID:"<<GetCurrentProcessId()<<std::endl;
    std::cout<<"LoadLibraryA:"<<(void*)LoadLibraryA<<std::endl;
    std::cout<<"CreateRemoteThread:"<<(void*)CreateRemoteThread<<std::endl;
    std::cout<<"test:"<<(void*)test<<std::endl;
    std::cout<<GetCurrentProcessId()<<' '<<(void*)test<<std::endl;
    std::cin.get();
    return 0;
}
