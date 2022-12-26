extern sum_of_three			    	; extern function sum_of_three declared in kmain.c
extern exponent					; extern function exponent declared in kmain.c
global loader

MAGIC_NUMBER    equ 0x1BADB002              	; define the magic number constant
FLAGS           equ 0x0                     	; multiboot flags
CHECKSUM        equ -MAGIC_NUMBER           	; calculate checksum 
                                            	; (magic_number + checksum + flags should be 0)

KERNEL_STACK_SIZE equ 4096                      ; size of stack (4 KB)

section .bss
    align 4                                     ; align at 4 bytes
    kernel_stack:                               ; label points to start of stack
        resb KERNEL_STACK_SIZE                  ; reserve uninitialised stack memory for kernel

section .text
align 4                                     	; 4 byte aligning the code
    dd MAGIC_NUMBER                         	; write magic_number,
    dd FLAGS                                	; flags
    dd CHECKSUM                                 ; and checksum to the machine code
    
loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp register to top of stack (start of the stack)

    push dword 5                                ; arg3
    push dword 3                                ; arg2
    push dword 1                                ; arg1
    call sum_of_three                           ; call sum_of_three, result will be in eax
    
    mov ebx,eax					; moves the result of sum_of_three to the ebx register
    
    push 2					; arg2
    push 5					; arg1
    call exponent				; call exponent, result will be in eax
    
.loop:
    jmp .loop					; loop forever
