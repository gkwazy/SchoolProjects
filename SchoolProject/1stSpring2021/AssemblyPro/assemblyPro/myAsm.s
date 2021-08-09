section .text
global _myGTOD
global _sayHello
global _myPuts

extern _puts

section   .text

_myGTOD:
    sub     rsp, 16
    mov     rax, 0x2000074
    mov     rdi, rsp
    mov     rsi, 0
    ;syscall
    mov     rax, [rsp]
    mov     rdx, [rsp+8]
    add     rsp, 16
    ret

_sayHello:
    push    rbp
    mov     rbp, rsp
    mov     rdi, helloString
    call    _puts
    pop     rbp
    ret

_myPuts:
    mov rax,0x2000004
    mov rdx, rsi
    mov rsi, rdi
    mov rdi, 1
    syscall
    ret
    
    
section .rodata
    helloString: db "hello",0


