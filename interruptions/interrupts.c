#include "interrupts.h"

static struct idtEntry segments[NUM_OF_SIGNALS];

static struct idtDescriptor idtr;

void idt_set_descriptor(unsigned char vector, void *isr, unsigned char flags)
{
    struct idtEntry *descriptor = &segments[vector];

    descriptor->offset_l = (unsigned int)isr & 0xFFFF;
    descriptor->kernel_cs = 0x08;
    descriptor->attributes = flags;
    descriptor->offset_h = (unsigned int)isr >> 16;
    descriptor->reserved = 0;
}

void idtr_init()
{
    extern void* isr_stub_table[];

    idtr.address = (unsigned long)&segments[0];
    idtr.size = (unsigned short)(sizeof(struct idtDescriptor) * NUM_OF_SIGNALS) - 1;

    for (unsigned short vector = 0; vector < NUM_OF_SIGNALS; vector++)
    {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }

    idtb(idtr);
}

void interrupt_handler(__attribute__((unused)) struct cpuState reg_state, __attribute__((unused)) struct stackState stack_state, unsigned int itr_code)
{
    switch (itr_code)
    {
    default:
        break;
    }
}