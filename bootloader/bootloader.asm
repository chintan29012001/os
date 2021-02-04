bits 16
org 0x7c00

boot:
	mov ax, 0x2401
	int 0x15
	mov ax, 0x3
	int 0x10
	cli
	lgdt [lgdt_pointer]
	mov eax, cr0
	or eax,0x1
	mov cr0, eax
	jmp CODE_SEG:boot4
lgdt_start:
	dq 0x0
lgdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
lgdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
lgdt_end:
lgdt_pointer:
	dw lgdt_end - lgdt_start
	dd lgdt_start

CODE_SEG equ lgdt_code - lgdt_start
DATA_SEG equ lgdt_data - lgdt_start

bits 32
boot4:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esi,message
	mov ebx,0xb8000
	jmp .pool

.pool:
	lodsb
	or al,0
	jz pr
	or eax,0x0f00
	mov word [ebx], ax
	add ebx,2
	jmp .pool

pr:
	mov edx, cr0
	mov ecx, 32        
	jmp .pool3

.pool3:
    mov eax, 00000f30h   
    shl edx, 1           
    adc eax, 0           
    mov [ebx], ax
    add ebx, 2
    dec ecx
    jnz .pool3
    lodsb
    or al,0
    jz stop	

stop:
	cli
	hlt
message: db 'Hello world! cr0 ',0

times 510 - ($-$$) db 0
dw 0xaa55
