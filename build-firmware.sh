#!/bin/bash

BUILD_PATH=.pio/build/m5stack-stamps3

current_version=$(head -n 1 version)

mkdir -p generated_firmwares

# Build the firmware
platformio run --environment m5stack-stamps3

# Generate bin file to use in M5Burner
esptool.py --chip esp32s3 merge_bin -o generated_firmwares/Cardputer.Mouse.Jiggler.v$current_version.bin 0x0 $BUILD_PATH/bootloader.bin 0x8000 $BUILD_PATH/partitions.bin 0x10000 $BUILD_PATH/firmware.bin
