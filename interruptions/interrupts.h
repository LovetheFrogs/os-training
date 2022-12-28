#ifndef INCLUDE_INTERRUPTS_H
#define INCLUDE_INTERRUPTS_H

/* Number of signals added to the IDT */
#define NUM_OF_SIGNALS 3

/** idtDescriptor is a data structure used to contain the start address and size of the
 *  Interrupt Descriptor Table. It simulates the following bit configuration:
 *
 *          Bit: | 47 - 32 | 31 - 0  |
 *      Content: |  size   | address |
 */
struct idtDescriptor
{
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

/** idtEntry is a data structure used to contain the values inside an Entry of the
 *  Interrupt Descriptor Table. It simulates the following bit configuration:
 *
 *          Bit: | 63       48 | 47 | 46 45 | 44 | 43 | 42 41 40 | 39 38 37 | 36 35 34 32 | 31            16 | 15       0 |
 *      Content: | offset high | P  | DPL   | 0  | D  | 1  1  0  | 0  0  0  | reserved    | segment selector | offset low |
 */
struct idtEntry
{
    unsigned short offset_l;
    unsigned short kernel_cs;
    unsigned char reserved;
    unsigned char attributes;
    unsigned short offset_h;
} __attribute__((packed));

/** cpuState is a custom data structure used to catch the values of the registers
 *  when the C function interrupt_handler is called.
 */
struct cpuState
{
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
} __attribute__((packed));

/** stackState is a custom data structure used to catch the values on the stack when
 *  the C function interrupt_handler is called.
 */
struct stackState
{
    unsigned int error_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
} __attribute__((packed));

/** idtb:
 *  Function idtb takes the atributes of an Interrupt Descriptor Table (namely it's size
 *  and address where it starts) and signals the CPU, using the lidt assembly instruction,
 *  on this information so it uses this data to comply with interruption handling.
 *
 *  @param descriptor data structure holding the size and address of IDT
 */
void idtb(struct idtDescriptor descriptor);

void idt_set_descriptor(unsigned char vector, void* isr, unsigned char flags);

void idtr_init();

void interrupt_handler(struct cpuState reg_state, struct stackState stack_state, unsigned int itr_code);

#endif /* INCLUDE_INTERRUPTIONS_H */