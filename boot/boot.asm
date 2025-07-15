[BITS 16]
[ORG 0x7C00]

; Boot sector constants
KERNEL_OFFSET equ 0x1000
KERNEL_SECTORS equ 16          ; Adjust based on kernel size

start:
    ; Initialize segment registers
    mov ax, 0x0000
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00             ; Stack grows downward from boot sector
    
    ; Clear screen
    mov ah, 0x00
    mov al, 0x03               ; 80x25 text mode
    int 0x10
    
    ; Print boot message
    mov si, boot_msg
    call print_string
    
    ; Reset disk drive
    mov ah, 0x00
    mov dl, 0x80               ; First hard drive
    int 0x13
    jc disk_error
    
    ; Load kernel from disk
    mov bx, KERNEL_OFFSET      ; Load kernel to 0x1000
    mov dh, 0x00               ; Head 0
    mov dl, 0x80               ; Drive 0x80 (first hard drive)
    mov ch, 0x00               ; Cylinder 0
    mov cl, 0x02               ; Sector 2 (sector 1 is boot sector)
    mov al, KERNEL_SECTORS     ; Number of sectors to read
    mov ah, 0x02               ; BIOS read sectors function
    
    int 0x13
    jc disk_error
    
    ; Check if we read the expected number of sectors
    cmp al, KERNEL_SECTORS
    jne disk_error
    
    ; Print kernel loaded message
    mov si, kernel_loaded_msg
    call print_string
    
    ; Set up basic GDT for protected mode
    cli                        ; Disable interrupts
    lgdt [gdt_descriptor]
    
    ; Enable A20 line (allows access to memory above 1MB)
    call enable_a20
    
    ; Switch to protected mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    
    ; Far jump to flush CPU pipeline and enter protected mode
    jmp CODE_SEG:init_pm

disk_error:
    mov si, disk_error_msg
    call print_string
    jmp hang

; Print string function (16-bit real mode)
print_string:
    mov ah, 0x0E
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

; Enable A20 line
enable_a20:
    ; Try fast A20 gate first
    in al, 0x92
    test al, 2
    jnz .done
    or al, 2
    and al, 0xFE
    out 0x92, al
.done:
    ret

; 32-bit protected mode initialization
[BITS 32]
init_pm:
    ; Set up segment registers for protected mode
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Set up stack
    mov ebp, 0x90000
    mov esp, ebp
    
    ; Print protected mode message
    mov esi, pm_msg
    call print_string_pm
    
    ; Jump to kernel
    call KERNEL_OFFSET
    
    ; If kernel returns, hang
    jmp hang

; Print string function (32-bit protected mode)
print_string_pm:
    mov edx, 0xb8000           ; Video memory address
.loop:
    mov al, [esi]
    cmp al, 0
    je .done
    mov ah, 0x0F               ; White on black
    mov [edx], ax
    add edx, 2
    inc esi
    jmp .loop
.done:
    ret

hang:
    jmp hang

; Global Descriptor Table
gdt_start:
    ; Null descriptor
    dd 0x0
    dd 0x0

gdt_code:
    ; Code segment descriptor
    ; Base=0x0, Limit=0xfffff
    ; 1st flags: (present)1 (privilege)00 (descriptor type)1 -> 1001b
    ; Type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010b
    ; 2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 1100b
    dw 0xffff      ; Limit (bits 0-15)
    dw 0x0         ; Base (bits 0-15)
    db 0x0         ; Base (bits 16-23)
    db 10011010b   ; 1st flags, type flags
    db 11001111b   ; 2nd flags, Limit (bits 16-19)
    db 0x0         ; Base (bits 24-31)

gdt_data:
    ; Data segment descriptor
    ; Same as code segment except for the type flags:
    ; Type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
    dw 0xffff      ; Limit (bits 0-15)
    dw 0x0         ; Base (bits 0-15)
    db 0x0         ; Base (bits 16-23)
    db 10010010b   ; 1st flags, type flags
    db 11001111b   ; 2nd flags, Limit (bits 16-19)
    db 0x0         ; Base (bits 24-31)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1    ; Size of GDT
    dd gdt_start                  ; Start address of GDT

; Define segment selectors
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; Data section
boot_msg db 'Kyro OS - Bootloader Starting...', 0x0D, 0x0A, 0
kernel_loaded_msg db 'Kernel loaded successfully!', 0x0D, 0x0A, 0
disk_error_msg db 'Disk read error!', 0x0D, 0x0A, 0
pm_msg db 'Entered 32-bit protected mode', 0

; Boot sector signature
times 510-($-$$) db 0
dw 0xAA55
