#include "../drivers/io.h"
#include "pic.h"

/** pic_acknowledge:
 *  Acknowledges an interrupt from either master PIC or slave PIC
 *
 *  @param itr The number of the interrupt
 */
void pic_acknowledge(unsigned int itr)
{
    if (itr < PIC_1_OFFSET || itr > PIC_2_END)
    {
        return;
    }

    if (itr < PIC_2_OFFSET)
    {
        outb(PIC_1_COMMAND, PIC_ACKNOWLEDGE);
    }
    else
    {
        outb(PIC_2_COMMAND, PIC_ACKNOWLEDGE);
    }
}

/** pic_remap:
 *  Remap PIC controllers with new vector offsets rather than default
 *  8h and 70h. Vectors of master and slave PIC will become offset..offset + 7
 *  for each respective offset.
 * 
 *  @param offset1 vector offset for master PIC
 *  @param offset2 vector offset for slave PIC
 */
void pic_remap(int offset1, int offset2)
{
    outb(PIC_1_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
    outb(PIC_2_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);

    outb(PIC_1_DATA, offset1);
    outb(PIC_2_DATA, offset2);

    outb(PIC_1_DATA, 4);
    outb(PIC_2_DATA, 2);

    outb(PIC_1_DATA, PIC_ICW4_8086);
    outb(PIC_2_DATA, PIC_ICW4_8086);

    outb(PIC_1_DATA, 0xFD);
    outb(PIC_2_DATA, 0xFF);

    // Enable interrupts
    asm("sti");
}