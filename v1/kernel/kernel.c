// kernel.c

#include <linux/kernel.h>

void start_kernel(void) {
    printk(KERN_INFO "Kyro Kernel started\n");

    // Initialize the kernel
    init_kernel();

    // Start the operating system
    start_os();
}

void init_kernel(void) {
    // Initialize the memory management unit (MMU)
    init_mmu();

    // Initialize the interrupt handlers
    init_interrupts();

    // Initialize the device drivers
    init_drivers();
}

void start_os(void) {
    // Start the operating system
    asm volatile("jmp %0" :: "r" (os_entry_point));
}

void init_mmu(void) {
    // Initialize the MMU
    // Set up the page tables
    uint32_t *page_table = (uint32_t *)0x1000;
    page_table[0] = 0x00000003; // kernel code
    page_table[1] = 0x00400003; // kernel data
    page_table[2] = 0x00800003; // user code
    page_table[3] = 0x00c00003; // user data

    // Enable paging
    asm volatile("movl %0, %%cr3" :: "r" (page_table));
    asm volatile("movl %cr0, %eax");
    asm volatile("orl $0x80000000, %eax");
    asm volatile("movl %eax, %cr0");
}

void init_interrupts(void) {
    // Initialize the interrupt handlers
    // Set up the IDT
    uint32_t *idt = (uint32_t *)0x10000;
    idt[0] = (uint32_t)interrupt_handler; // divide by zero
    idt[1] = (uint32_t)interrupt_handler; // debug
    idt[2] = (uint32_t)interrupt_handler; // NMI
    idt[3] = (uint32_t)interrupt_handler; // breakpoint
    idt[4] = (uint32_t)interrupt_handler; // overflow
    idt[5] = (uint32_t)interrupt_handler; // bounds check
    idt[6] = (uint32_t)interrupt_handler; // invalid opcode
    idt[7] = (uint32_t)interrupt_handler; // coprocessor not available
    idt[8] = (uint32_t)interrupt_handler; // double fault
    idt[9] = (uint32_t)interrupt_handler; // coprocessor segment overrun
    idt[10] = (uint32_t)interrupt_handler; // invalid TSS
    idt[11] = (uint32_t)interrupt_handler; // segment not present
    idt[12] = (uint32_t)interrupt_handler; // stack segment fault
    idt[13] = (uint32_t)interrupt_handler; // general protection fault
    idt[14] = (uint32_t)interrupt_handler; // page fault
    idt[15] = (uint32_t)interrupt_handler; // reserved // Load the IDT
    asm volatile("lidt (%0)" :: "r" (idt));
}

void init_drivers(void) {
    // Initialize the device drivers
    // Initialize the keyboard driver
    init_keyboard();

    // Initialize the display driver
    init_display();
}

void interrupt_handler(void) {
    // Handle the interrupt
    // Get the interrupt number
    uint32_t interrupt_number;
    asm volatile("movl %%eax, %0" : "=r" (interrupt_number));

    // Handle the interrupt
    switch (interrupt_number) {
        case 0:
            // Divide by zero
            printk(KERN_ERR "Divide by zero\n");
            break;
        case 1:
            // Debug
            printk(KERN_ERR "Debug\n");
            break;
        case 2:
            // NMI
            printk(KERN_ERR "NMI\n");
            break;
        case 3:
            // Breakpoint
            printk(KERN_ERR "Breakpoint\n");
            break;
        case 4:
            // Overflow
            printk(KERN_ERR "Overflow\n");
            break;
        case 5:
            // Bounds check
            printk(KERN_ERR "Bounds check\n");
            break;
        case 6:
            // Invalid opcode
            printk(KERN_ERR "Invalid opcode\n");
            break;
        case 7:
            // Coprocessor not available
            printk(KERN_ERR "Coprocessor not available\n");
            break;
        case 8:
            // Double fault
            printk(KERN_ERR "Double fault\n");
            break;
        case 9:
            // Coprocessor segment overrun
            printk(KERN_ERR "Coprocessor segment overrun\n");
            break;
        case 10:
            // Invalid TSS
            printk(KERN_ERR "Invalid TSS\n");
            break;
        case 11:
            // Segment not present
            printk(KERN_ERR "Segment not present\n");
            break;
        case 12:
            // Stack segment fault
            printk(KERN_ERR "Stack segment fault\n");
            break;
        case 13:
            // General protection fault
            printk(KERN_ERR "General protection fault\n");
            break;
        case 14:
            // Page fault
            printk(KERN_ERR "Page fault\n");
            break;
        case 15:
            // Reserved
            printk(KERN_ERR "Reserved\n");
            break;
        default:
            // Unknown interrupt
            printk(KERN_ERR "Unknown interrupt\n");
            break;
    }
}

void init_keyboard(void) {
    // Initialize the keyboard driver
    // Set up the keyboard interrupt handler
    uint32_t *idt = (uint32_t *)0x10000;
    idt[0x21] = (uint32_t)keyboard_interrupt_handler;

    // Load the IDT
    asm volatile("lidt (%0)" :: "r" (idt));
}

void keyboard_interrupt_handler(void) {
    // Handle the keyboard interrupt
    // Get the keyboard scan code
    uint32_t scan_code;
    asm volatile("inb $0x60, %al" : "=a" (scan_code));

    // Handle the keyboard scan code
    switch (scan_code) {
        case 0x01:
            // Escape
            printk(KERN_INFO "Escape\n");
            break;
        case 0x02:
            // 1
            printk(KERN_INFO "1\n");
            break;
        case 0x03:
            // 2
            printk(KERN_INFO "2\n");
            break;
        case 0x04:
            // 3
            printk(KERN_INFO "3\n");
            break;
        case 0x05:
            // 4
            printk(KERN_INFO "4\n");
            break;
        case 0x06:
            // 5
            printk(KERN_INFO "5\n");
            break;
        case 0x07:
            // 6
            printk(KERN_INFO "6\n");
            break;
        case 0x08:
            // 7
            printk(KERN_INFO "7\n");
            break;
        case 0x09:
            // 8
            printk(KERN_INFO "8\n");
            break;
        case 0x0a:
            // 9
            printk(KERN_INFO "9\n");
            break;
        case 0x0b:
            // 0
            printk(KERN_INFO "0\n");
            break;
        case 0x0c:
            // -
            printk(KERN_INFO "-\n");
            break;
        case 0x0d:
            // =
            printk(KERN_INFO "=\n");
            break;
        case 0x0e:
            // Backspace
            printk(KERN_INFO "Backspace\n");
            break;
        case 0x0f:
            // Tab
            printk(KERN_INFO "Tab\n");
            break;
        case 0x10:
            // Q
            printk(KERN_INFO "Q\n");
            break;
        case 0x11:
            // W
            printk(KERN_INFO "W\n");
            break;
        case 0x12:
            // E
            printk(KERN_INFO "E\n");
            break;
        case 0x13:
            // R
            printk(KERN_INFO "R\n");
            break;
        case 0x14:
            // T
            printk(KERN_INFO "T\n");
            break;
        case 0x15:
            // Y
            printk(KERN_INFO "Y\n");
            break;
        case 0x16:
            // U
            printk(KERN_INFO "U\n");
            break;
        case 0x17:
            // I
            printk(KERN_INFO "I\n");
            break;
        case 0x18:
            // O
            printk(KERN_INFO "O\n");
            break;
        case 0x19:
            // P
            printk(KERN_INFO "P\n");
            break;
        case 0x1a:
            // [
            printk(KERN_INFO "[\n");
            break;
        case 0x1b:
            // ]
            printk(KERN_INFO "]\n");
            break;
        case 0x1c:
            // Enter
            printk(KERN_INFO "Enter\n");
            break;
        case 0x1d:
            // Ctrl
            printk(KERN_INFO "Ctrl\n");
            break;
        case 0x1e:
            // A
            printk(KERN_INFO "A\n");
            break;
        case 0x1f:
            // S
            printk(KERN_INFO "S\n");
            break;
        case 0x20:
            // D
            printk(KERN_INFO "D\n");
            break;
        case 0x21:
            // F
            printk(KERN_INFO "F\n");
            break;
        case 0x22:
            // G
            printk(KERN_INFO "G\n");
            break;
        case 0x23:
            // H
            printk(KERN_INFO "H\n");
            break;
        case 0x24:
            // J
            printk(KERN_INFO "J\n");
            break;
        case 0x25:
            // K
            printk(KERN_INFO "K\n");
            break;
        case 0x26:
            // L
            printk(KERN_INFO "L\n");
            break;
        case 0x27:
            // ;
            printk(KERN_INFO ";\n");
            break;
        case 0x28:
            // '
            printk(KERN_INFO "'\n");
            break;
        case 0x29:
            // `
            printk(KERN_INFO "`\n");
            break;
        case 0x2a:
            // Shift
            printk(KERN_INFO "Shift\n");
            break;
        case 0x2b:
            // \
            printk(KERN_INFO "\\\n");
            break;
        case 0x2c:
            // Z
            printk(KERN_INFO "Z\n");
            break;
        case 0x2d:
            // X
            printk(KERN_INFO "X\n");
            break;
        case 0x2e:
            // C
            printk(KERN_INFO "C\n");
            break;
        case 0x2f:
            // V
            printk(KERN_INFO "V\n");
            break;
        case 0x30:
            // B
            printk(KERN_INFO "B\n");
            break;
        case 0x31:
            // N
            printk(KERN_INFO "N\n");
            break;
        case 0x32:
            // M
            printk(KERN_INFO "M\n");
            break;
        case 0x33:
            // ,
            printk(KERN_INFO ",\n");
            break;
        case 0x34:
            // .
            printk(KERN_INFO ".\n");
            break;
        case 0x35:
            // /
            printk(KERN_INFO "/\n");
            break;
        case 0x36:
            // F1
            printk(KERN_INFO "F1\n");
            break;
        case 0x37:
            // F2
            printk(KERN_INFO "F2\n");
            break;
        case 0x38:
            // F3
            printk(KERN_INFO "F3\n");
            break;
        case 0x39:
            // F4
            printk(KERN_INFO "F4\n");
            break;
        case 0x3a:
            // F5
            printk(KERN_INFO "F5\n");
            break;
        case 0x3b:
            // F6
            printk(KERN_INFO "F6\n");
            break;
        case 0x3c:
            // F7
            printk(KERN_INFO "F7\n");
            break;
        case 0x3d:
            // F8
            printk(KERN_INFO "F8\n");
            break;
        case 0 x3e:
            // F9
            printk(KERN_INFO "F9\n");
            break;
        case 0x3f:
            // F10
            printk(KERN_INFO "F10\n");
            break;
        case 0x40:
            // F11
            printk(KERN_INFO "F11\n");
            break;
        case 0x41:
            // F12
            printk(KERN_INFO "F12\n");
            break;
        default:
            // Unknown key
            printk(KERN_INFO "Unknown key\n");
            break;
    }
}

void init_display(void) {
    // Initialize the display driver
    // Set up the display mode
    uint32_t *display_mode = (uint32_t *)0x10000;
    display_mode[0] = 0x00000003; // 640x480x16

    // Load the display mode
    asm volatile("movl %0, %%eax" :: "r" (display_mode));
    asm volatile("int $0x10");
}
