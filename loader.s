global loader                               ; entry symbol for ELF (see linker.ld)

MAGIC_NUMBER    equ 0x1BADB002              ; define the magic number constant
FLAGS           equ 0x0                     ; multiboot flags
CHECKSUM        equ -MAGIC_NUMBER           ; calculate checksum 
                                            ; (magic_number + checksum + flags should be 0)

section .text                               ; start of code section (.text)
align 4                                     ; 4 byte aligning the code
    dd MAGIC_NUMBER                         ; write magic_number,
    dd FLAGS                                ; flags
    dd CHECKSUM                             ; and checksum to the machine code

loader:                                     ; loader label used as entry point in linker.ld
    mov eax, 0xCAFEBABE                     ; place number 0xCAFEBABE into eax register

.loop:
    jmp .loop                               ; loop forever (while true)