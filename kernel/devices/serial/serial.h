/******************************************************************************
 * Serial driver for Platypus OS                                              *
 * (c) DamieFC 2021                                                           *
 ******************************************************************************/

#ifdef SERIAL_H
    #undef SERIAL_H
    #define SERIAL_H
#else
    #ifndef SERIAL_H
    #define SERIAL_H
struct serial_drvr_platypusos{
    void serial_init(void);
    void serial_read(int port);
    char serial_write(char[] value, port);
}
