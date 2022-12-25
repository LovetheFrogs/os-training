#include "drivers/framebuffer.h"
#include "drivers/serialport.h"

void kmain()
{
    char buf[] = "This is lovethefrogs' OS.";
    char res[1];
    fb_clear();
    res[0] = fb_write(buf, sizeof(buf)) + 49;
    serial_write(SERIAL_COM1_BASE, res, sizeof(res));

    char buff[] = "Check the out log to see result of previous print!";
    fb_write(buff, sizeof(buff));
}