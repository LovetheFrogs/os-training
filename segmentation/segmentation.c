#include "segmentation.h"

/** segments is an array of N positions, where N is the number of entries
 *  of the GDT. Each entry of the array is a gdtEntry.
 */
static struct gdtEntry segments[NUM_OF_SEGMENTS];

/** set_gdt_entry:
 *  Sets the value of segment[index] to the desired values.
 *
 *  @param index        Index of the entry you want to change
 *  @param base         Base address of the entry
 *  @param limit        Limit address of the entry
 *  @param access_byte  Acces byte of the entry
 *  @param flags        Wanted flags for that entry
 */
void set_gdt_entry(int index, unsigned int base, unsigned int limit, unsigned char access_byte, unsigned char flags)
{
    segments[index].base0 = base & 0xFFFF;
    segments[index].base1 = (base >> 16) & 0xFF;
    segments[index].base2 = (base >> 24) & 0xFF;

    segments[index].limit0 = limit & 0xFFFF;
    segments[index].limit1_flags = (limit >> 16) & 0xF;
    segments[index].limit1_flags |= (flags << 4) & 0xF0;

    segments[index].access_byte = access_byte;
}

/** create_gdt:
 *  Creates a Global Descriptor Table of N entries and gives each entry the values it needs.
 *  Then, it tells the CPU where is the GDT and loads the selectors to the desired positions.
 */
void create_gdt()
{
    segments[0].base0 = 0;
    segments[0].base1 = 0;
    segments[0].base2 = 0;
    segments[0].limit0 = 0;
    segments[0].limit1_flags = 0;
    segments[0].access_byte = 0;

    struct gdtDescriptor *descriptor = (struct gdtDescriptor *)segments;
    descriptor->size = (sizeof(struct gdtEntry) * NUM_OF_SEGMENTS) - 1;
    descriptor->address = (unsigned int)segments;

    set_gdt_entry(1, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_CODE_TYPE, SEGMENT_FLAGS);
    set_gdt_entry(2, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_DATA_TYPE, SEGMENT_FLAGS);

    gdtb(*descriptor);
    load_selector();
}