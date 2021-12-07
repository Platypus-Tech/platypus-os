#!/bin/sh

CONFIG_USERNAME=`whoami`
CONFIG_ARCH=`arch`
CONFIG_USERMODE=n

if [ ! -d kernel/include/generated/ ]; then
    mkdir kernel/include/generated/
fi

if [ -f kernel/include/generated/config.h ]; then
   rm kernel/include/generated/config.h
fi

echo "#ifndef _GENERATED_CONFIG_H\n#define _GENERATED_CONFIG_H\n\n#define CONFIG_ARCH \"$CONFIG_ARCH\"\n#define CONFIG_USERNAME \"$CONFIG_USERNAME\"\n#define CONFIG_USERMODE '$CONFIG_USERMODE'\n\n#endif //_GENERATED_CONFIG_H" > kernel/include/generated/config.h
