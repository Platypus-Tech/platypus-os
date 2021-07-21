#include "ata_pio.h"
#include <kernel/ports.h>
#include <printm/printm.h>

int ata_drive_chk(int drive) {
  outp(drive, 0x1F6);
  outp(ATA_SECTOR_COUNT, 0);
  outp(ATA_SECTOR_NUMBER, 0);
  outp(ATA_CYLINDER_LOW, 0);
  outp(ATA_CYLINDER_HIGH, 0);

  outp(ATA_IDENTIFY, ATA_COMMAND_PORT);

  int i = inp(ATA_COMMAND_PORT);

  if (i == 0) {
    printm(3, "ATA PIO: Drive doesn't exist\n");
  } else {
    for (;;) {
      int status = inp(ATA_COMMAND_PORT);
      int low = inp(ATA_CYLINDER_LOW);
      int high = inp(ATA_CYLINDER_HIGH);

      if (low != 0 && high != 0) {
        printm(3, "ATA PIO: Drive is not ATA\n");
        return 1;
      }
    }
  }
}
