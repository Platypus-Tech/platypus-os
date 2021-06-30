#include "ata_pio.h"
#include <kernel/ports.h>
#include <printm/printm.h>

#define ATA_COMMAND_PORT 0x1F7

void ata_drive_chk(int drive) {
  outp(drive, 0x1F6);
  outp(ATA_SECTOR_COUNT, 0);
  outp(ATA_SECTOR_NUMBER, 0);
  outp(ATA_CYLINDER_LOW, 0);
  outp(ATA_CYLINDER_HIGH, 0);

  outp(ATA_IDENTIFY, ATA_COMMAND_PORT);

  int i = inp(ATA_COMMAND_PORT);

  if (i == 0) {
    printm(3, "Drive doesn't exist\n");
  }
}
