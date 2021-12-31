; Copyright (c) 2021 github.com/System233
; 
; This software is released under the MIT License.
; https://opensource.org/licenses/MIT
    global x64call_exec
    global _x64call_exec
    global x64call_strcmp
    global _x64call_strcmp
    global x64call_isin32
    global _x64call_isin32
    global x64call_dlsym
    global _x64call_dlsym
    global x64call_dlwalk
    global _x64call_dlwalk
    section .text
; uint64_t x64call_exec(size_t n,uint64_t,...)
;x86: esp+4 +8 +C +10
;x64: rcx,rdx,r8,r9,esp+28,+30
_x64call_isin32:
x64call_isin32:
    bits 64
    xor eax,eax
    neg rax
    ret
sw32:
    mov dword [rsp+0x4],0x23
    retf
sw64:
    bits 32
    pop eax
    push 0x33
    push eax
    retf

x64call_strcmp:
_x64call_strcmp:
    bits 64
    mov al,[rcx]
    mov ah,[rdx]
    test ax,ax
    jz .equals
    cmp al,ah
    jl .less
    jg .great
    
    inc rcx
    inc rdx
    jmp x64call_strcmp
.less:
    mov rax,-1
    ret
.great:
    mov rax,1
    ret
.equals:
    xor rax,rax
    ret

;x64call_dlwalk(char const*name);
x64call_dlwalk:
_x64call_dlwalk:
    bits 32
    call x64call_isin32
    test eax,eax
    jz .func
    call sw64
    bits 64
    ; mov rcx,[rsp+4]
    movsxd rcx,DWORD [rsp+4]
    sub rsp,8
    call .func
    mov [rsp],rax
    call sw32
    bits 32
    pop eax
    pop edx
    ret
.func:
    bits 64
    push rsi                        ;+8
    push rdi                        
    push rcx                        ;0x18
    mov rsi, gs:[0x60]               ;PEB
    mov rsi, [rsi+0x18]              ;PEB.Ldr
    mov rsi, [rsi+0x30]              ;PEB.Ldr.InInitializationOrderModuleList
    mov rdi,rsi
    sub rsp,0x10
.loop:

    mov rcx,[rsi+0x10]              ;LDR_DATA_TABLE_ENTRY.dllBase
    test rcx,rcx
    jz .next
    mov rdx,[rsp+0x10]
    call x64call_dlsym
    test rax,rax
    jnz .end

.next:
    mov rsi,[rsi]                  ;LDR_DATA_TABLE_ENTRY.InInitializationOrderModuleList.Flink
    cmp rsi,rdi
    jne .loop
.end:
    add rsp,0x10
    pop rcx
    pop rdi
    pop rsi
    ret
;x64call_dlsym(uint64_t handle,char const*name);
x64call_dlsym:
_x64call_dlsym:
    bits 32
    call x64call_isin32
    test eax,eax
    jz .func
    call sw64
    bits 64
    mov rcx,[rsp+4]
    movsxd rdx,DWORD [rsp+0xC]
    sub rsp,8
    call .func
    mov [rsp],rax
    call sw32
    bits 32
    pop eax
    pop edx
    ret
.func:
    bits 64
    test rcx,rcx
    jz .walk
    push rbx
    push rsi
    push rdi
    push r10
    push rdx
    mov rsi,rcx                         ;LDR_DATA_TABLE_ENTRY.DllBase 
    movsxd rax,DWORD [rsi+0x3C]      ;IMAGE_DOS_HEADER.e_lfanew
    lea rdi,[rsi+rax+0x18+0x70]      ;IMAGE_NT_HEADERS64.OptionalHeader.DataDirectory
    movsxd rax,DWORD [rdi]           ;DataDirectory.VirtualAddress 
    lea rdi,[rsi+rax]                ;IMAGE_EXPORT_DIRECTORY
    movsxd rbx,DWORD [rdi+0x18]      ;IMAGE_EXPORT_DIRECTORY.NumberOfNames
    movsxd rax,DWORD [rdi+0x20]      ;IMAGE_EXPORT_DIRECTORY.AddressOfNames
    lea r10,[rsi+rax]       ;Names
.loop:
    xor rax,rax
    test rbx,rbx
    jz .end
    dec rbx
    lea rcx,[r10+rbx*4]              ;IMAGE_EXPORT_DIRECTORY.AddressOfNames
    movsxd rax,DWORD [rcx]
    lea rcx,[rsi+rax]
    mov rdx,[rsp]
    call x64call_strcmp
    test rax,rax
    jnz .loop
    movsxd rax,DWORD [rdi+0x24]              ;IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals
    lea rax,[rax+rbx*2]
    add rax,rsi
    xor rbx,rbx
    mov bx,[rax]
    movsxd rax,DWORD [rdi+0x1C]              ;IMAGE_EXPORT_DIRECTORY.AddressOfFunctions
    lea rcx,[rax+rbx*4]
    add rcx,rsi
    movsxd rax,DWORD [rcx]
    add rax,rsi
.end:
    pop rcx
    pop r10
    pop rdi
    pop rsi
    pop rbx
    ret
.walk:
    mov rcx,rdx
    sub rsp,8
    call x64call_dlwalk
    add rsp,8
    ret
x64call_exec:  
_x64call_exec:
    bits 32
    call x64call_isin32
    test eax,eax
    jz .func
    call sw64
    bits 64
    mov r12d,[rsp]
    add rsp,4
    mov rcx,[rsp]
    mov rdx,[rsp+8]
    mov r8,[rsp+0x10]
    mov r9,[rsp+0x18]
    call .func
    sub rsp,0x4
    mov [rsp],r12d
    push rax
    call sw32
    bits 32
    pop eax
    pop edx
    ret
.func:
    bits 64
    test rdx,rdx
    jz .end
    push rsi
    push rdi        ;+16+8=0x28
    push rbx        ;0x30
    lea rsi,[rsp+0x30]
    lea rcx,[rcx*8]
    mov rbx,rcx
    mov rax,rdx
    sub rsp,rcx
    mov rdi,rsp
    rep movsb
    mov rcx,r8
    mov rdx,r9
    mov r8,[rsp+0x10]
    mov r9,[rsp+0x18]
    call rax
    add rsp,rbx
    pop rbx
    pop rdi
    pop rsi
    ret
.end:
    xor rax,rax
    ret

