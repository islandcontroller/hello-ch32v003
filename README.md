# hello-ch32v003 [![GitHub license](https://img.shields.io/github/license/islandcontroller/hello-ch32v003?style=flat-square)](LICENSE) [![Discord server link](https://img.shields.io/badge/discord-WCH%20Community-white?style=flat-square&logo=discord)](https://t.co/Qbblvmfbae)

A simple "Hello World"-like project for the ultra low-cost WCH CH32V003 RISC-V MCU.

<p align="center"><img src="scr.png" /></p>

This project contains a simple set of modules to get the MCU running in a minimal configuration:
  - Serial I/O on USART1 (connected to WCH-LinkE USART)
  - SysTick enabled and using auto-reload feature

## Requirements

* Hardware
  * WCH CH32V003F4P6-EVT+WCH-LinkE Starter Kit (available from LCSC, [PartNr `C5236707`](https://www.lcsc.com/product-detail/Microcontroller-Units-MCUs-MPUs-SOCs_WCH-Jiangsu-Qin-Heng-CH32V003F4P6-EVT-WCH-LinkE_C5236707.html))
    * Starter Kit includes WCH-LinkE Debugger
  * 6 pcs. female-female jumper wires
* Software
  * [MounRiver Studio Community](http://www.mounriver.com/) (as of March 2023, a [manual OpenOCD update](#manual-openocd-update) is needed)
  * Serial terminal program, e.g. [PuTTy](https://www.putty.org/) or minicom

### Manual OpenOCD Update

The current release (V1.30) or MounRiver Studio Community does not include the updated OpenOCD build required for WCH-LinkE support. In order to update the debugger, perform the following steps:

* Download the [MounRiver Studio V1.84 Update](http://file.mounriver.com/upgrade/MounRiver_Update_V184.zip) package
* Extract the package into a temporary folder
* Copy the contained `toolchain` folder to your **local** MounRiver Studio Community installation
* Confirm overwrite of all files in the `toolchain` folder

### Hardware Setup

Follow instructions from the [WCH-LinkE User Manual](http://www.wch-ic.com/downloads/WCH-LinkUserManual_PDF.html) for connecting the debugger to your EVT board.

| WCH-LinkE Pin | EVT Board Pin |
|---------------|---------------|
| `RST`         | `NRST / PD7`  |
| `3V3`         | `VCC` (*)     |
| `GND`         | `GND`         |
| `SWDIO/TMS`   | `PD1`         |
| `TX`          | `PD6`         |
| `RX`          | `PD5`         |

*) For powering the target from your WCH-LinkE debugger. Omit this if you want to power the EVT board via its own USB port.

## Usage

* Clone this repository using the following command. Note the use of the `--recursive` tag.
  ```
  git clone --recursive https://github.com/islandcontroller/hello-ch32v003
  ```
* Load this project in **MounRiver Studio Community** and build the executable
* Open a serial terminal on the WCH-LinkE programmer's VCP (**115200 Baud, 8N1**)
* Flash the firmware to the MCU using the provided `.launch` script
* Resume execution once breakpoint in `main()` is reached
* Press `?` in the serial terminal to show available commands

## Licensing

If not stated otherwise in the specific file, the contents of this project are licensed under the MIT License. The full license text is provided in the [`LICENSE`](LICENSE) file.

    SPDX-License-Identifier: MIT

## Help and References

* [openwch/ch32v003](https://github.com/openwch/ch32v003) Manufacturer EVT demos and documentation
* [WCH-IC: CH32V003DS0.pdf](http://www.wch-ic.com/downloads/CH32V003DS0_PDF.html) MCU Datasheet
* [WCH-IC: CH32V003RM.pdf](http://www.wch-ic.com/downloads/CH32V003RM_PDF.html) MCU Reference Manual
* [WCH-IC: QingKeV2_Processor_Manual.pdf](http://www.wch-ic.com/downloads/QingKeV2_Processor_Manual_PDF.html) Processor Core Manual

If you're looking for further information about WCH products, check out their community Discord server: 
[![Discord server link](https://img.shields.io/badge/discord-WCH%20Community-white?style=flat-square&logo=discord)](https://t.co/Qbblvmfbae)