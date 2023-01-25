#include "serialport.h"

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor mentioned above
 */
void serial_configure_baud_rate(unsigned char com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data lenght of 8 bits, no parity bits, one stop bit and break control
 *  disabeled.
 *
 *  @param com The serial port to configure
 */
void serial_configure_line(unsigned short com)
{
    /* Bit:      | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content:  | d | b | prty  | s | dl  |
     * Value:    | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/** serial_configure_fifo_queue:
 *  Configures the FIFO buffer for the I/O port COM. It is set to enable the
 *  FIFO queue, clear both reciever and transmission FIFO queues and use 14
 *  bytes as size of queue.
 *
 *  @param com The serial port to configure
 */
void serial_configure_fifo_queue(unsigned short com)
{
    /* Bit:      | 7 6  | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content:  | lvl  | bs | r | dma | clt | clr | e |
     * Value:    | 1 1  | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/** serial_configure_modem:
 *  Configures the modem control register for the I/O port COM. It is set to
 *  enable both rts (ready to transmit) and dtr (data terminal ready). Every
 *  other pin is not used so it's set to 0.
 *
 *  @param com The COM port
 */
void serial_configure_modem(unsigned short com)
{
    /* Bit:      | 7 | 6 | 5  | 4  | 3   | 2   | 1    | 0   |
     * Content:  | r | r | af | lb | ao2 | ao1 | rts  | dtr |
     * Value:    | 0 | 0 | 0  | 0  | 0   | 0   | 1    | 1   |= 0x03
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return     0 if the transmit FIFO queue is not empty
 *              1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/** serial_write_byte:
 *  Writes the byte data to the I/O port COM.
 *
 *  @param com  The COM port
 *  @param data The byte to write
 */
void serial_write_byte(unsigned short com, char data)
{
    outb(com, data);
}

/** serial_configure:
 *  Configures the serial port COM to the values stablished by the functions
 *  called within the function. The parameter divisor is used to call the
 *  serial_configure_baud_rate function.
 *
 *  @param com     The COM port
 *  @param divisor The divisor mentioned above
 */
void serial_configure(unsigned short com, unsigned short divisor)
{
    serial_configure_baud_rate(com, divisor);
    serial_configure_line(com);
    serial_configure_fifo_queue(com);
    serial_configure_modem(com);
}

/** serial_write:
 *  Writes the character buffer buf to the I/O port COM. Cheks status of
 *  FIFO queue. If it is not empty, jumps to next iteration and tries to
 *  send the current byte again. If byte is sent, update index to next
 *  byte to send.
 *
 *  @param com The COM port to write to
 *  @param buf Character buffer to write to the I/O port
 *  @param len Lenght of the character buffer
 *  @return      0 in case all the buffer has been written
 *             > 0 if there are characters left to print
 *             < 0 if trash has been written to the port
 */
int serial_write(unsigned short com, char *buf, unsigned int len)
{
    unsigned int index = 0;
    serial_configure(com, 4);
    while (index < len)
    {
        if (serial_is_transmit_fifo_empty(com))
        {
            serial_write_byte(com, buf[index]);
            index++;
        }
    }

    return len - (index + 1);
}