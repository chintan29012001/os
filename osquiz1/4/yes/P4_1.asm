section .text
global sum
; ebx ecx edx esi
sum:
    mov eax,[esp+4]
    add eax,[esp+8]
    add eax,[esp+12]
    add eax,[esp+16]
    ret






