global gdtb                 ; make the label gdtb visible outside gdt.s
global load_selector        ; make the label load_selector visible outside gdt.s

; gdtb - takes the address of a struct that
;        specifies start and size of the GDT
; stack: [esp + 4] the address of the struct
;        [esp    ] the return address
gdtb:
    lgdt [esp + 4]          ; puts start and size of GDT to the ones in the struct
    ret                     ; return to caller function

; load_selector - loads the segment selector registers
load_selector:
    mov ax, 0x10            ; set ax register to 0x10, offset of third segment (READ-WRITE)
    mov ds, ax              ; set data segment to ax (0x10)
    mov ss, ax              ; set stack segment to ax (0x10)
    mov es, ax              ; set extra segment to ax (0x10)
    mov gs, ax              ; set general purpose segment gs to ax (0x10)
    mov fs, ax              ; set general purpose segment fs to ax (0x10)
    jmp 0x08:flush_cs       ; set code segment to 0x08 and jumps to flush_cs
                            ; 0x08 is the direction of the second segment (READ-EXECUTE)

flush_cs:
    ret                     ; return to caller function