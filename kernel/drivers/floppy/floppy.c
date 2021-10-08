#include "floppy.h"
#include <kernel/ports.h>
#include <kernel/printm.h>
#include <pit/pit.h>
#include <stdint.h>

static const char *drive_types[7] = {"no drive",          "360 KB 5.25 Drive",
                                     "1.2 MB 5.25 Drive", "720 KB 3.5 Drive",
                                     "1.44 MB 3.5 Drive", "2.88 MB 3.5 Drive",
                                     "unknown drive"};

static const char *drive_status[3] = {"error", "invalid", "drive"};

int floppy_motor_state = 0;

void detect_drives_floppy() {
  outp(0x70, 0x10);
  uint8_t drives = inp(0x71);
  printm("Floppy drive 0: %s, ", drive_types[drives >> 4]);
  printm("1: %s\n", drive_types[drives & 0xF]);
}

void write_command_floppy(int base, char command) {
  for (int i = 0; i < 300; i++) {
    sleep_pit(1);

    if (0x80 & inp(base + MAIN_STATUS_REGISTER)) {
      return (void)outp(base + DATA_FIFO, command);
    }
  }

  printm("Floppy: write_command_floppy: timeout\n");
}

uint8_t read_data_floppy(int base) {
  for (int i = 0; i < 300; i++) {
    sleep_pit(1);

    if (0x80 & inp(base + MAIN_STATUS_REGISTER)) {
      return inp(base + DATA_FIFO);
    }
  }

  printm("Floppy: read_data_floppy: timeout\n");
}

void check_interrupt_floppy(int base, int *st0, uint16_t *cyl) {
  write_command_floppy(base, SENSE_INTERRUPT);
  *st0 = read_data_floppy(base);
  *cyl = read_data_floppy(base);
}

int calibrate_floppy(int base) {
  int st0, cyl = -1;

  motor_floppy(base, MOTOR_ON);

  for (int i = 0; i < 4; i++) {
    write_command_floppy(base, RECALIBRATE);
    write_command_floppy(base, 0);
    sleep_pit(2);
    check_interrupt_floppy(base, &st0, &cyl);

    if (st0 & 0xC0) {
      printm("Floppy: calibrate: status = %s\n", drive_status[st0 >> 6]);
      continue;
    }

    if (!cyl) {
      motor_floppy(base, MOTOR_OFF);
      return 0;
    }
  }

  printm("Floppy: error: cannot calibrate\n");
  motor_floppy(base, MOTOR_OFF);
  return 1;
}

int reset_floppy(int base) {
  outp(base + DIGITAL_OUTPUT_REGISTER, 0x00);
  outp(base + DIGITAL_OUTPUT_REGISTER, 0x0C);

  sleep_pit(3);

  int st0, cyl;
  check_interrupt_floppy(base, &st0, &cyl);

  outp(base + CONFIGURATION_CONTROL_REGISTER, 0x00);
  write_command_floppy(base, SPECIFY);
  write_command_floppy(base, 0xDF);
  write_command_floppy(base, 0x02);

  if (calibrate_floppy(base)) {
    return -1;
  }
}

void motor_floppy(int base, int state) {
  if (state) {
    if (!floppy_motor_state) {
      outp(base + DIGITAL_OUTPUT_REGISTER, 0x1C);
      sleep_pit(0.50);
    }
    floppy_motor_state = MOTOR_ON;
  } else {
    if (floppy_motor_state == MOTOR_WAIT) {
      printm("Floppy: notice: motor is already waiting\n");
    }
    floppy_motor_state = MOTOR_WAIT;
  }
}
