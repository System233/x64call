/**
 * Copyright (c) 2021 github.com/System233
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <stdio.h>
#include <Windows.h>
#include <x64call.h>


int main(int argc, char const *argv[])
{
    printf("ntdll.dll:%p\n",GetModuleHandleA("ntdll.dll"));
    printf("NtCreateThreadEx:%#llX\n",x64call_dlwalk("NtCreateThreadEx"));
    printf("LoadLibraryA:%#llX\n",x64call_dlwalk("LoadLibraryA"));
    printf("LoadLibraryW:%#llX\n",x64call_dlwalk("LoadLibraryW"));
    printf("NtWaitForSingleObject:%#llX\n",x64call_dlwalk("NtWaitForSingleObject"));
    printf("RtlCopyMemory:%#llX\n",x64call_dlwalk("RtlCopyMemory"));
    printf("AllocateLocallyUniqueId:%#llX\n",x64call_dlwalk("AllocateLocallyUniqueId"));
    return 0;
}
