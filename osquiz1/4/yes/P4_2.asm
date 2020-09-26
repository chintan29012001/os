section .text
global sum
sum:
    mov rax,[rbp-4]
    add rax,[rbp-8]
    add rax,[rbp-12]
    add rax,[rbp-16]
    ret
