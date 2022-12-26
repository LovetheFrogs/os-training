#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/** outb:
 *  Sends the given data to the given I/O port. Function defined in io.s
 *
 *  @param port The I/O port to send data to
 *  @param data The data to be sent to the I/O port
 */
void outb(unsigned short port, unsigned char data);

/** inb:
 *  Read a byte from the I/O port. Function defined in io.s
 *
 *  @param  port The address of the i/O port
 *  @return      The read byte
 */
unsigned char inb(unsigned short port);

#endif /* INCLUDE_IO_H */