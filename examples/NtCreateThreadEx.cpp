/**
 * Copyright (c) 2021 github.com/System233
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */


#include <Windows.h>
#include <x64call>
#include <iostream>
#include <string>

using PNtCreateThreadEx=DWORD64(
    PDWORD64                 ThreadHandle,
    ACCESS_MASK             DesiredAccess,
    LPVOID                  ObjectAttributes,
    HANDLE                  ProcessHandle,
    DWORD64  lpStartAddress,
    LPVOID                  lpParameter,
    BOOL                    CreateSuspended,
    DWORD64                 dwStackSize,
    DWORD64                 dwStackCommit,
    DWORD64                 dwStackReserve,
    LPVOID                  lpBytesBuffer
);
using PNtWaitForSingleObject=DWORD64(DWORD64 handle,DWORD64 time);
int main(int argc, char const *argv[])
{
    int pid;
    uint64_t addr;
    std::string dllPath;
    std::cout<<"TargetPID LoadLibraryAddr>";
    std::cin>>pid>>std::hex>>addr;
    std::cout<<"PID:"<<pid<<std::endl;
    std::cout<<"Addr:"<<std::hex<<addr<<std::dec<<std::endl;
    std::cout<<"DllPath>";
    std::cin>>dllPath;
    HANDLE hProc=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
    std::cout<<"hProc:"<<hProc<<std::endl;

    uint64_t hThread=NULL;
    void*dllName=VirtualAllocEx(hProc,NULL,dllPath.size(),MEM_COMMIT,PAGE_READWRITE);
    std::cout<<"dllName:"<<dllName<<std::endl;
    WriteProcessMemory(hProc,dllName,dllPath.data(),dllPath.size(),NULL);

    x64call::x64<PNtCreateThreadEx>::call("NtCreateThreadEx",&hThread,0x1FFFFF,NULL,hProc,addr,dllName,FALSE,0,0,0,NULL);
    std::cout<<"hThread:"<<(HANDLE)hThread<<std::endl;
    // x64call::x64<PNtWaitForSingleObject>::call("NtWaitForSingleObject",hThread,INFINITE);
    WaitForSingleObject((HANDLE)hThread,INFINITE);
    VirtualFreeEx(hProc,dllName,dllPath.size(),MEM_RELEASE);
    std::cout<<"VirtualFreeEx"<<std::endl;
    return 0;
}
