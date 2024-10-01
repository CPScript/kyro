all: os-image.bin

boot.bin: boot/boot.asm
    nasm -f bin boot/boot.asm -o boot.bin

kernel.bin: kernel/kernel.c kernel/user.c kernel/fs.c kernel/terminal.c
    gcc -ffreestanding -c kernel/kernel.c -o kernel.o
    gcc -ffreestanding -c kernel/user.c -o user.o
    gcc -ffreestanding -c kernel/fs.c -o fs.o
    gcc -ffreestanding -c kernel/terminal.c -o terminal.o
    ld -Ttext 0x1000 --oformat binary -o kernel.bin kernel.o user.o fs.o terminal.o

os-image.bin: boot.bin kernel.bin
    cat boot.bin kernel.bin > os-image.bin

clean:
    rm -f *.bin *.o
