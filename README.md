# STM32F4 Dual CDC (USB ACM) Reference Project

This repository contains a **minimal, reference implementation of a dual USB CDC (ACM) device** for the **STM32F4 series**, specifically targeting the **WeAct STM32F411 “Black Pill” (25 MHz HSE)** board.

The project is intended as a **known-good baseline** for implementing multiple CDC interfaces on STM32F4 using **libopencm3**, with explicit USB descriptors and deterministic endpoint mapping.

---

## Target Hardware

- **MCU:** STM32F411CEU6  
- **USB:** OTG_FS (Full Speed)  
- **Clock:** External 25 MHz crystal (HSE)  
- **Board:** WeAct STM32F411 Black Pill (25 MHz variant)

This project assumes:
- OTG_FS peripheral
- External 25 MHz HSE
- No external VBUS sensing (self-powered or fixed-power designs)

### WeAct Black Pill Reference

Official WeAct STM32F411 Black Pill repository:  
https://github.com/WeActStudio/WeActStudio.STM32F411CEU6

---

## Repository Layout

stm32-dual-cdc/
├── libopencm3/      (git submodule)
├── src/             (application source)
├── Makefile
└── README.md

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

## Flashing

Example using OpenOCD:

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program dual_cdc.elf verify reset exit"

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

