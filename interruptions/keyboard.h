#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_MAX_ASCII 89

unsigned char read_scan_code(void);

unsigned char convert_scan_code(unsigned char scan_code);

#endif /* INCLUDE_KEYBOARD_H */