# hello-ch32v003 (VSCode) [![GitHub license](https://img.shields.io/github/license/islandcontroller/hello-ch32v003?style=flat-square)](LICENSE) [![Discord server link](https://img.shields.io/badge/discord-WCH%20Community-white?style=flat-square&logo=discord)](https://t.co/Qbblvmfbae)

A simple "Hello World"-like project for the ultra low-cost WCH CH32V003 RISC-V MCU.

<p align="center"><img src="scr_vscode.png" /></p>

This project contains a simple set of modules to get the MCU running in a minimal configuration:
  - Serial I/O on USART1 (connected to WCH-LinkE USART)
  - SysTick enabled and using auto-reload feature

## Requirements

* Hardware
  * WCH CH32V003F4P6-EVT+WCH-LinkE Starter Kit (available from LCSC, [PartNr `C5236707`](https://www.lcsc.com/product-detail/Microcontroller-Units-MCUs-MPUs-SOCs_WCH-Jiangsu-Qin-Heng-CH32V003F4P6-EVT-WCH-LinkE_C5236707.html))
    * Starter Kit includes WCH-LinkE Debugger
  * 6 pcs. female-female jumper wires
* Software
  * Linux OS or WSL installation
  * [Docker Engine](https://docs.docker.com/engine/install/debian/) (running within WSL if applicable)
  * VSCode [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension
  * (WSL only) [usbipd-win](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) (Windows *and* WSL parts installed!)

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
* Open the folder in VSCode
* Connect WCH-Link debug probe
  * (WSL only) attach to WSL using `usbipd wsl attach --busid <...> -a`.
* Run the command "**Dev Containers: Reopen in Container**"
  * On first launch, you may need to copy the udev rules from `/tmp/MRS/beforeinstall` into your **host's** `/etc/udev/rules.d/` directory
  * Then, reload the rules using `sudo udevadm control --reload-rules` and `sudo udevadm trigger`.
  * Afterwards, restart the devcontainer.
* Upon prompt, select the "**GCC x.x riscv-none-embed**" CMake Kit. 
* Run "**CMake: Configure**"
* Build using "**CMake: Build [F7]**"
* Open a new Terminal tab and start OpenOCD

      openocd -f /opt/openocd/bin/wch-riscv.cfg

* Split the terminal tab using the `[|]`-Button or press `Ctrl + Shift + 5`. Then launch the serial monitor:

      cu -l /dev/ttyACM0 -s 115200

  **To close the connection later on, press ESC/ENTER, type `~.` (tilde, dot) and wait for 3 seconds.**

* Start debugging using "**Debug: Start Debugging [F5]**"
* Continue execution once the breakpoint in `main()` is reached.
* Type `?` in the serial monitor Terminal tab to show available commands.

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