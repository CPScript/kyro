section .text
    global _start

_start:
    mov ah, 0x0E
    mov si, message
.next_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .next_char
.done:
    ; Load the kernel
    mov ax, 0x1000   ; Load kernel at 0x1000
    jmp ax

section .data
message db 'Booting Kyro OS...', 0
