    
global checkGreater
global _start
    section .data  
string1: db    "1",10
string0: db    "0",10
    section .text

checkGreater:
    cmp rdi,rsi
    jg printOne
    jmp printZero

_start:
    mov rdi,0 ;value for x
    mov rsi,1 ;value for y
    jmp checkGreater


printOne:
    ;code for equal
    mov rax,1
    mov rdi,1
    mov rsi,string1
    mov rdx,2
    syscall
    jmp exit

printZero:
    mov rax,1
    mov rdi,1
    mov rsi,string0
    mov rdx,2
    syscall
    jmp exit
exit:
    mov rdi,0
    mov rax,60
    syscall