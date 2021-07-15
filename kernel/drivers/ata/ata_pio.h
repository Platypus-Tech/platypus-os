#ifndef _DRIVERS_ATA_PIO_H
#define _DRIVERS_ATA_PIO_H

#define ATA_PRIMARY_BUS_PORT 0x1F0
#define ATA_PRIMARY_BUS_CTRL_PORT 0x3F6
#define ATA_SECONDARY_BUS_PORT 0x170
#define ATA_SECONDARY_BUS_CTRL_PORT 0x376

// ATA Ports
#define ATA_DATA 0
#define ATA_ERROR 1
#define ATA_FEATURES 1
#define ATA_SECTOR_COUNT 2
#define ATA_SECTOR_NUMBER 3
#define ATA_CYLINDER_LOW 4
#define ATA_CYLINDER_HIGH 5
#define ATA_DRIVE 6
#define ATA_STATUS 7
#define ATA_COMMAND 7
#define ATA_COMMAND_PORT 0x1F7

#define ATA_ALTERNATE_STATUS 0
#define ATA_DEVICE_CONTROL 0
#define ATA_DRIVE_ADDR 1

// ATA Status Register
#define ATA_ERR 0
#define ATA_IDX 1
#define ATA_CORR 2
#define ATA_DRQ 3
#define ATA_SRV 4
#define ATA_DF 5
#define ATA_RDY 6
#define ATA_BSY 7

// ATA Commands
#define ATA_IDENTIFY 0xEC

void ata_drive_chk(int drive);

#endif //_DRIVERS_ATA_PIO_H
