echo Running NASM
nasm -f elf32 kernel.asm -o kasm.o
echo Running GCC
gcc -m32 -c kernel.c -o kc.o
echo Running Linker
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
