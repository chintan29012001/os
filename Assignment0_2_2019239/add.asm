
global add
global sub

add:
    add    rdi, rsi
    mov    rax,rdi
    ret
sub:
    sub    rdi, rsi
    mov    rax,rdi
    ret

