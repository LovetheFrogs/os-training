extern interrupt_handler

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push dword 0
    push dword %1
    jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push dword %1
    jmp  common_interrupt_handler
%endmacro

common_interrupt_handler:
    push eax
    push ebx
    push ecx
    push edx
    push ebp
    push esi
    push edi

    call interrupt_handler

    pop edi
    pop esi
    pop ebp
    pop edx
    pop ecx
    pop ebx
    pop eax

    add esp, 8
    iret

no_error_code_interrupt_handler 33