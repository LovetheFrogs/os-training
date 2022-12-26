global idtb                 ; make the label idtb visible outside idt.s

; idtb - takes the adress of a struct wich specifies start address
;        and size of IDT and tells the CPU this information.
; stack: [esp + 4] the address of the struct
;        [esp    ] the return address
idtb:
    mov eax, [esp + 4]      ; move the values in the position [esp + 4] of the stack to eax register
    lidt [eax]              ; load the values of the IDT located in eax to the CPU
    ret                     ; return to caller function