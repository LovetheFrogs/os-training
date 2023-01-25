#include "../drivers/io.h"
#include "keyboard.h"

/** read_scan_code:
 *  Reads a scan code from the keyboard
 *
 *  @return The scan code (NOT ASCII)
 */
unsigned char read_scan_code(void)
{
    return inb(KEYBOARD_DATA_PORT);
}

/** convert_scan_code:
 *  Converts a scan code to the desired ASCII value. Currently using ISO105 (ISO/ES)
 *
 *  @param scan_code The scan code of the pressed key
 *  @return The desired ASCII value
 */
unsigned char convert_scan_code(unsigned char scan_code)
{
    unsigned char ISO105_ascii[256] =
        {
            0x00, 0x00, '1', '2', '3', '4', '5', '6', '7', '8',         // 0 - 9
            '9', '0', 0x00, 0x00, 0x00, 0x00, 'q', 'w', 'e', 'r',         // 10 - 19
            't', 'y', 'u', 'i', 'o', 'p', '`', '+', '\n', 0x00,       // 20 - 29
            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0x00,           // 30 - 39
            0x00, 0x00, 0x00, 0x00, 'z', 'x', 'c', 'v', 'b', 'n',          // 40 - 49
            'm', ',', '.', '-', 0x00, '*', 0x00, ' ', 0x00, 0x00,       // 50 - 59
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60 - 69
            0x00, '7', '8', '9', '-', '4', '5', '6', '+', '1',          // 70 - 79
            '2', '3', '0', '.', 0x00, 0x00, '<', 0x00, 0x00, 0x00,      // 80 - 89
        };

    return ISO105_ascii[scan_code];
}