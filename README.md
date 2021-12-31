# x64call

Call 64bit function in 32bit process;  
32位进程调用64位函数, CPP类型安全
## Usage

### IN CPP
```cpp

#include <Windows.h>
#include <x64call>
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
    DWORD64 hThread;
    x64call::x64<PNtCreateThreadEx>::call("NtCreateThreadEx",&hThread,0x1FFFFF,NULL,hProc,addr64,pParam,FALSE,0,0,0,NULL);

    //or
    char const name[]="NtCreateThreadEx";
    x64call::x64<PNtCreateThreadEx>::call<name>(&hThread,0x1FFFFF,NULL,hProc,addr64,pParam,FALSE,0,0,0,NULL);
  
```

### IN C
```c
#include <Windows.h>
#include <x64call.h>
DWORD64 hThread;
x64call_exec(
    11,                                //number of target function args
    x64call_dlwalk("NtCreateThreadEx"),//64bit function addr
    (uint64_t)0x1FFFFF,                //args...
    (uint64_t)NULL,
    (uint64_t)hProc,
    (uint64_t)addr64,
    (uint64_t)pParam,
    (uint64_t)FALSE,
    (uint64_t)0,
    (uint64_t)0,
    (uint64_t)0,
    (uint64_t)NULL,
)
```

## Notes
不支持浮点类型和结构体传值
