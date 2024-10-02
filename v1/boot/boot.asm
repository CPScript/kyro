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
    mov eax, 0x100000
    mov ecx, 0x1000
    mov edx, 0x1000
    call read_usb

    ; Return the address of the kernel
    ret

read_usb:
    ; Read from the USB drive using the BIOS
    mov eax, 0x13
    mov ebx, 0x100000
    mov ecx, 0x1000
    mov edx, 0x1000
    int 0x13
    ret
