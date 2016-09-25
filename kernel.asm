;;kernel.asm
bits 32                        ;set to 32bit mode
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002           ;magic number to indentify header for multiboot
        dd 0x00                 ;flags field - we have no flags so equal to 0
        dd - (0x1BADB002+0x00)  ;checksum
global start
extern smain                   ;smain is the starting point defined in the c file

start:
  cli                         ;disable interrupts
  mov esp, stack_space        ;set stack pointer
  call smain                  ;call the c file
  hlt



section .bss
resb  8192                    ;reserve 8kb for the stack
stack_space:
