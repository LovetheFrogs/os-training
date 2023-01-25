; set EAX register to some easy-to-read number 
; to use when checking bochslog.txt file
bits 32
start:
mov eax, 0xDEADBEEF

; enter an infinite loop
jmp start