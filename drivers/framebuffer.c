#include "framebuffer.h"

/* Reference to framebuffer start memory position */
static char *fb = (char *)0x000B8000;
unsigned int scr = 0;

/** read_cell
 *  Reads the specified cell.
 *
 *  @param i The position to read
 */
char read_cell(unsigned int i)
{
    return fb[i];
}

/** fb_scroll
 *  Scrolls the screen one position.
 */
static void fb_scroll()
{
    unsigned int r, c;

    for (r = 1; r < NUM_OF_ROWS; r++)
    {
        for (c = 0; c < NUM_OF_COLS; c++)
        {
            fb_write_cell(TO_POSITION(r - 1, c), read_cell(TO_POSITION(r, c)), FB_BLACK, FB_WHITE);
        }
    }

    for (c = 0; c < NUM_OF_COLS; c++)
    {
        fb_write_cell(TO_POSITION(NUM_OF_ROWS - 1, c), ' ', FB_BLACK, FB_WHITE);
    }
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/** fb_move_cursor
 *  Moves the cursor of the framebuffer to the given position.
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos & 0x00FF));
}

/** fb_write
 *  Writes the character buffer buf to the framebuffer.
 *
 *  @param buf Character buffer to write to the framebuffer
 *  @param len Lenght of the character buffer
 *  @return    Return number of characters left to print.
 */
int fb_write(char *buf, unsigned int len)
{
    unsigned int i;

    for (i = 0; i < len; i++)
    {
        if (scr / NUM_OF_COLS == NUM_OF_ROWS - 1)
        {
            fb_scroll();
            scr -= NUM_OF_COLS;
        }

        fb_write_cell(scr * 2, *(buf + i), FB_BLACK, FB_WHITE);
        fb_move_cursor(scr);
        scr++;
    }

    return len - (i + 1);
}

/** fb_clear
 *  Clears the framebuffer.
 */
void fb_clear()
{
    for (unsigned int r = 0; r < NUM_OF_ROWS; r++)
    {
        for (unsigned int c = 0; c < NUM_OF_COLS; c++)
        {
            fb_write_cell(TO_POSITION(r, c), ' ', FB_BLACK, FB_WHITE);
        }
    }
}

/** fb_clear_cell:
 *  Clears the cell scr, used when backspace is detected.
 *
 *  @param scr The position to delete
 */
void fb_clear_cell(unsigned int scr)
{
    fb_write_cell(scr * 2, ' ', FB_BLACK, FB_WHITE);
    if (scr != 0)
        fb_move_cursor(scr - 1);
}