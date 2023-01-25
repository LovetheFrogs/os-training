#ifndef INCLUDE_SEGMENTATION_H
#define INCLUDE_SEGMENTATION_H

#define NUM_OF_SEGMENTS 3

#define SEGMENT_BASE 0
#define SEGMENT_LIMIT 0xFFFFF

#define SEGMENT_CODE_TYPE 0x9A
#define SEGMENT_DATA_TYPE 0x92

#define SEGMENT_FLAGS 0x0C

/** gdtDescriptor is the descriptor containing the address and size of the
 *  Global Descriptor Table
 */
struct gdtDescriptor
{
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

/** gdtEntry is the format of each entry of the GDT */
struct gdtEntry
{
    unsigned short limit0;
    unsigned short base0;
    unsigned char base1;
    unsigned char access_byte;
    unsigned char limit1_flags;
    unsigned char base2;
} __attribute__((packed));

/** gdtb:
 *  Puts the start address and size of GDT table to the given struct.
 *  Function defined in gdt.s
 *
 *  @param descriptor struct of type gdtDescriptor where data about GDT is stored
 */
void gdtb(struct gdtDescriptor descriptor);

/** load_selector:
 *  Loads the segment selector registers. Data registers need a mov to 0x10
 *  as the segment at this offset has read and write privileges. One segment
 *  can not have both write and execute privileges, hence the need of another
 *  segment, of offset 0x08 for the code segment. Function defined in gdt.s
 */
void load_selector();

void set_gdt_entry(int index, unsigned int base, unsigned int limit, unsigned char access_byte, unsigned char flags);

void create_gdt();

#endif /* INCLUDE_SEGMENTATION_H */