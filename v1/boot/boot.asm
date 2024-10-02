; boot.asm

; Multiboot header
section .multiboot
align 4
dd 0x1BADB002             ; magic number
dd 0x00000003             ; flags
dd - (0x1BADB002 + 0x00000003) ; checksum

; Bootloader code
section .text
global _start
_start:
    ; Set up the stack
    mov esp, 0x7c00

    ; Load the kernel into memory
    mov eax, 0x100000
    mov ecx, 0x1000
    mov edx, 0x1000
    call load_kernel

    ; Jump to the kernel
    jmp eax

load_kernel:
    ; Read the kernel from the USB drive
    mov eax, 0x13
    mov ebx, 0x100000
    mov ecx, 0x1000
    mov edx, 0x1000
    int 0x13

    ; Check if the read was successful
    jc read_error

    ; Return the address of the kernel
    ret

read_error:
    ; Print an error message
    mov eax, 0x4
    mov ebx, 0x100000
    mov ecx, error_message
    mov edx, error_message_len
    int 0x10

    ; Halt the system
    hlt

error_message db 'Error reading kernel from USB drive', 0
error_message_len equ $ - error_message
