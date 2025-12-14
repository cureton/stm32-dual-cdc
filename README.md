# STM32F4 Dual CDC (USB ACM) Reference Project

This repository contains a **minimal, reference implementation of a dual USB CDC (ACM) device** for the **STM32F4 series**, specifically targeting the **WeAct STM32F411 “Black Pill” (25 MHz HSE)** board.

The project is intended as a **known-good baseline** for implementing multiple CDC interfaces on STM32F4 using **libopencm3**
---

## Target Hardware

- **MCU:** STM32F411CEU6  
- **USB:** OTG_FS (Full Speed)  
- **Clock:** External 25 MHz crystal (HSE)  
- **Board:** WeAct STM32F411 Black Pill (25 MHz variant)

### WeAct Black Pill Reference

Official WeAct STM32F411 Black Pill repository:  
https://github.com/WeActStudio/WeActStudio.STM32F411CEU6

---
## Checkout (Including Submodules)

This project uses **libopencm3 as a git submodule**.

Clone the repository **with submodules**:

git clone --recurse-submodules git@github.com:cureton/stm32-dual-cdc.git  
cd stm32-dual-cdc

If you already cloned without submodules:

git submodule update --init --recursive

---

## Building libopencm3 (STM32F4)

libopencm3 must be built **before** building the application firmware.

cd libopencm3  
make TARGETS=stm32/f4

---

## Building the Dual CDC Firmware

After libopencm3 has been built:

cd ../src  
make

---

## Flashing - SWD interface

Example using OpenOCD:

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program dual_cdc.elf verify reset exit"

---

## Flashing - DFU-util 

Example using dfu-util:
Plug the black pill into the host computer whilst  holding the BOOT0 button 

verify that the device is in ROM DFU mode:
sudo dfu-util -l 

Program the binary file into the device:

sudo dfu-util -a 0  -s 0x08000000  -D usb_cdc_test.bin

Press the nRST button or unplug and plug in the device with new firmare. 



---

## USB Functionality

When connected to a Linux host, the device enumerates as:

- /dev/ttyACM0  
- /dev/ttyACM1  

Verify enumeration and descriptors with:

lsusb -v

---

## License

This project is provided as a reference implementation for educational and development use.  
libopencm3 is licensed under its own terms.

