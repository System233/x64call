/**
 * Copyright (c) 2021 github.com/System233
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */


#include <Windows.h>
#include <x64call.h>
#include <stdio.h>
char dllPath[MAX_PATH];

int main(int argc, char const *argv[])
{
    int pid;
    uint64_t addr;
    printf("TargetPID LoadLibraryAddr>");
    scanf("%d,%llx",&pid,&addr);
    printf("DllPath>");
    scanf("%s",dllPath);
    int len=strlen(dllPath);
    HANDLE hProc=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
    printf("hProc:%p\n",hProc);

    uint64_t hThread=NULL;
    void*dllName=VirtualAllocEx(hProc,NULL,len,MEM_COMMIT,PAGE_READWRITE);
    printf("dllName:%p\n",dllName);
    WriteProcessMemory(hProc,dllName,dllPath,len,NULL);
    x64call_exec(11,"NtCreateThreadEx",&hThread,0x1FFFFF,NULL,hProc,addr,dllName,FALSE,0,0,0,NULL);
    printf("hProc:0x%llx\n",hThread);
    WaitForSingleObject((HANDLE)hThread,INFINITE);
    VirtualFreeEx(hProc,dllName,len,MEM_RELEASE);
    printf("VirtualFreeEx\n");
    return 0;
}
