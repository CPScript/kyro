all: build-os-image

build-os-image: build-boot-loader build-kernel
    cat boot.bin kernel.bin > os-image.bin

build-boot-loader: boot/boot.asm
    nasm -f bin boot/boot.asm -o boot.bin

build-kernel: kernel/kernel.c kernel/user.c kernel/fs.c kernel/terminal.c kernel/networking.c
    gcc -ffreestanding -c kernel/kernel.c -o kernel.o
    gcc -ffreestanding -c kernel/user.c -o user.o
    gcc -ffreestanding -c kernel/fs.c -o fs.o
    gcc -ffreestanding -c kernel/terminal.c -o terminal.o
    gcc -ffreestanding -c kernel/networking.c -o networking.o
    ld -Ttext 0x1000 --oformat binary -o kernel.bin kernel.o user.o fs.o terminal.o networking.o

clean:
    rm -f *.bin *.o
