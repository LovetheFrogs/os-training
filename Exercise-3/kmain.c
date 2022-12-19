#include "framebuffer.c"

void kmain() {    
    /* Define the output to the framebuffer */    
    char buf[] = "Hello World!";
    
    /* Clear the screen at startup */
    fb_clear();

    /* Write the output defined at line 4 */
    fb_write(buf, sizeof(buf));
}