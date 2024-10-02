# Makefile for Kyro OS

# Compiler and linker flags
CC = gcc
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -ffreestanding
LDFLAGS = -m32 -nostdlib -Tlink.ld

# Source files
BOOT_SRC = boot/boot.asm
KERNEL_SRC = kernel/kernel.c
OS_SRC = os/main.c
SECURITY_SRC = security/encryption/aes.c security/secure-boot/secure-boot.c security/anonymity/tor.c
TOOLS_SRC = tools/usb-boot/syslinux.cfg
RAMFS_SRC = ramfs.c

# Object files
BOOT_OBJ = $(BOOT_SRC:.asm=.o)
KERNEL_OBJ = $(KERNEL_SRC:.c=.o)
OS_OBJ = $(OS_SRC:.c=.o)
SECURITY_OBJ = $(SECURITY_SRC:.c=.o)
RAMFS_OBJ = $(RAMFS_SRC:.c=.o)

# All object files
OBJ = $(BOOT_OBJ) $(KERNEL_OBJ) $(OS_OBJ) $(SECURITY_OBJ) $(RAMFS_OBJ)

# All source files
SRC = $(BOOT_SRC) $(KERNEL_SRC) $(OS_SRC) $(SECURITY_SRC) $(TOOLS_SRC) $(RAMFS_SRC)

# All header files
HDR = $(wildcard *.h)

# Default target
all: kernel.elf

# Compile and link the kernel
kernel.elf: $(OBJ)
    $(CC) $(LDFLAGS) -o kernel.elf $(OBJ)

# Compile the kernel
$(KERNEL_OBJ): $(KERNEL_SRC) $(HDR)
    $(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(KERNEL_OBJ)

# Compile the OS
$(OS_OBJ): $(OS_SRC) $(HDR)
    $(CC) $(CFLAGS) -c $(OS_SRC) -o $(OS_OBJ)

# Compile the security components
$(SECURITY_OBJ): $(SECURITY_SRC) $(HDR)
    $(CC) $(CFLAGS) -c $(SECURITY_SRC) -o $(SECURITY_OBJ)

# Compile the RAMFS
$(RAMFS_OBJ): $(RAMFS_SRC) $(HDR)
    $(CC) $(CFLAGS) -c $(RAMFS_SRC) -o $(RAMFS_OBJ)

# Assemble the bootloader
$(BOOT_OBJ): $(BOOT_SRC)
    nasm -f elf32 $(BOOT_SRC) -o $(BOOT_OBJ)

# Clean the object files
clean:
    rm -f $(OBJ)

# Clean the kernel
clean_kernel:
    rm -f kernel.elf

# Run the kernel
run: kernel.elf
    qemu-system-i386 -kernel kernel.elf
