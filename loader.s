extern kmain			    	                ; extern function sum_of_three declared in kmain.c
global loader

MAGIC_NUMBER    equ 0x1BADB002              	; define the magic number constant
FLAGS           equ 0x0                     	; multiboot flags
ALIGN_MODULES   equ 0x00000001                  ; tell GRUB to align modules

; calculate the checksum (all options + checksum should be 0)
CHECKSUM        equ -(MAGIC_NUMBER + FLAGS + ALIGN_MODULES)

KERNEL_STACK_SIZE equ 4096                      ; size of stack (4 KB)

section .bss
    align 4                                     ; align at 4 bytes
    kernel_stack:                               ; label points to start of stack
        resb KERNEL_STACK_SIZE                  ; reserve uninitialised stack memory for kernel

section .text
align 4                                     	; 4 byte aligning the code
    dd MAGIC_NUMBER                         	; write magic_number
    dd FLAGS                                	; flags
    dd ALIGN_MODULES                            ; write the align modules instruction
    dd CHECKSUM                                 ; and checksum to the machine code
    
loader:
    call kmain                                  ; call kmain, result will be in eax
    
.loop:
    jmp .loop					                ; loop forever
