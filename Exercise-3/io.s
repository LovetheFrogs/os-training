global outb                 ; make the label outb visible outside io.s

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] the return address
outb:
    mov al, [esp + 8]       ; move the data to be sent to the al register
    mov dx, [esp + 4]       ; move the address of the I/O port to the dx register
    out dx, al              ; send the data to the I/O port using the out function
    ret                     ; return to caller function