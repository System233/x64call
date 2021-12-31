/**
 * Copyright (c) 2021 github.com/System233
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <stdio.h>
#include <Windows.h>
#include <x64call>
int main(int argc, char const *argv[])
{
    printf("ntdll.dll:%p\n",GetModuleHandleA("ntdll.dll"));
    printf("NtCreateThreadEx:%#llX\n",x64call::dlwalk("NtCreateThreadEx"));
    printf("LoadLibraryA:%#llX\n",x64call::dlwalk("LoadLibraryA"));
    printf("LoadLibraryW:%#llX\n",x64call::dlwalk("LoadLibraryW"));
    printf("NtWaitForSingleObject:%#llX\n",x64call::dlwalk("NtWaitForSingleObject"));
    printf("RtlCopyMemory:%#llX\n",x64call::dlwalk("RtlCopyMemory"));
    printf("AllocateLocallyUniqueId:%#llX\n",x64call::dlwalk("AllocateLocallyUniqueId"));
    return 0;
}
