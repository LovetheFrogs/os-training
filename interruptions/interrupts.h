#ifndef INCLUDE_INTERRUPTS_H
#define INCLUDE_INTERRUPTS_H

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
    unsigned char atributes;
    unsigned short offset_h
} __attribute__((packed));

#endif /* INCLUDE_INTERRUPTIONS_H */