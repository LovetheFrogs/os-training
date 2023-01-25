#include "drivers/framebuffer.h"
#include "drivers/serialport.h"
#include "segmentation/segmentation.h"
#include "interruptions/interrupts.h"
#include "multiboot.h"

void init()
{
    create_gdt();
    serial_configure(SERIAL_COM1_BASE, 1);
    idtr_init();
}

void kmain(unsigned int ebx)
{
    init();
    char buf[] = "This is lovethefrogs' OS.";
    char res[1];
    fb_clear();

    res[0] = fb_write(buf, sizeof(buf)) + 49;
    serial_write(SERIAL_COM1_BASE, res, sizeof(res));

    char buff[] = "Check the out log to see result of previous print!";
    fb_write(buff, sizeof(buff));

    multiboot_info_t *mbinfo = (multiboot_info_t *)ebx;
    multiboot_module_t *module_data = (multiboot_module_t *)mbinfo->mods_addr;
    unsigned int address = module_data->mod_start;

    typedef void (*call_module_t)(void);
    call_module_t run = (call_module_t)address;
    run();
}