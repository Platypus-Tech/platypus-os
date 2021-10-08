#ifndef _DRIVERS_FLOPPY_H
#define _DRIVERS_FLOPPY_H

#include <stdint.h>

#define FLOPPY_BASE 0x03F0

enum floppy_registers {
  DIGITAL_OUTPUT_REGISTER = 0x3F2,
  MAIN_STATUS_REGISTER = 0x3F4,
  DATA_FIFO = 0x3F5,
  CONFIGURATION_CONTROL_REGISTER = 0x3F7
};

enum floppy_commands {
  SPECIFY = 3,
  WRITE_DATA = 5,
  READ_DATA = 6,
  RECALIBRATE = 7,
  SENSE_INTERRUPT = 8,
  SEEK = 15
};

enum floppy_motor_states { MOTOR_OFF = 0, MOTOR_ON, MOTOR_WAIT };

void detect_drives_floppy();
void write_command_floppy(int base, char command);
uint8_t read_data_floppy(int base);
void check_interrupt_floppy(int base, int *st0, uint16_t *cyl);
int calibrate_floppy(int base);
int reset_floppy(int base);
void motor_floppy(int base, int state);

#endif //_DRIVERS_FLOPPY_H
