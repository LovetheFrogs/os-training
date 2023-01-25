#include "interrupts.h"
#include "pic.h"
#include "keyboard.h"
#include "../drivers/io.h"
#include "../drivers/framebuffer.h"

static struct idtEntry segments[NUM_OF_SIGNALS];

static struct idtDescriptor idtr;

/** idt_set_descriptor:
 *  Sets the values for a descriptor fields
 *
 *  @param vector Descriptor to set values of
 *  @param isr Offset of the descriptor
 *  @param flags Flags for the descriptor
 */
void idt_set_descriptor(int vector, unsigned int isr, unsigned char flags)
{
    segments[vector].offset_h = (isr >> 16) & 0xFFFF;
    segments[vector].offset_l = (isr & 0xFFFF);
    segments[vector].kernel_cs = 0x08;
    segments[vector].reserved = 0;
    segments[vector].attributes = flags;
}

/** idtr_init:
 *  Initialises the Interrupt Descriptor Table
 */
void idtr_init()
{
    idt_set_descriptor(KEYBOARD_ITR, (unsigned int)interrupt_handler_33, 0x8E);

    idtr.address = (int)&segments;
    idtr.size = (unsigned short)(sizeof(struct idtDescriptor) * NUM_OF_SIGNALS);

    idtb((int)&idtr);
    pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
}

/** interrupt_handler:
 *  Default interrupt handler. Calls a different function depending on the interrupt
 *  detected by the CPU
 *
 *  @param reg_state State of the CPU registers
 *  @param stack_state State of the stack when interrupt is detected
 *  @param itr_code Code of the detected interrupt
 */
void interrupt_handler(__attribute__((unused)) struct cpuState reg_state, unsigned int itr_code, __attribute__((unused)) struct stackState stack_state)
{
    switch (itr_code)
    {
    case KEYBOARD_ITR:
        itr_33_handler();
        pic_acknowledge(itr_code);
        break;
    default:
        break;
    }
}

/** itr_33_handler:
 *  Handler for interrupt 33, called when a keyboard press is detected
 */
void itr_33_handler()
{
    extern unsigned int scr;
    unsigned char scan_code;
    scan_code = read_scan_code();
    if (scan_code <= KEYBOARD_MAX_ASCII)
    {
        unsigned char ascii;
        char buff[1];

        ascii = convert_scan_code(scan_code);
        buff[0] = ascii;

        if (scan_code == 14)
        {
            fb_clear_cell(scr);
            if (scr != 0)
                scr--;
        }
        else
        {
            fb_write(buff, sizeof(buff));
        }
    }
}
