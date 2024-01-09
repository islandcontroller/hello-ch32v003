# hello-ch32v003 (VSCode) [![GitHub license](https://img.shields.io/github/license/islandcontroller/hello-ch32v003?style=flat-square)](LICENSE) [![Discord server link](https://img.shields.io/badge/discord-WCH%20Community-white?style=flat-square&logo=discord)](https://t.co/Qbblvmfbae)

A simple "Hello World"-like project for the ultra low-cost WCH CH32V003 RISC-V MCU.

<p align="center"><img src="scr_vscode.png" /></p>

This project contains a simple set of modules to get the MCU running in a minimal configuration:
  - Serial I/O on USART1 (connected to WCH-LinkE USART)
  - TIM1 Channel 3 configured for PWM output to LED
  - SysTick enabled and using auto-reload feature

## Requirements

* Hardware
  * WCH CH32V003F4P6-EVT+WCH-LinkE Starter Kit (available from LCSC, [PartNr `C5236707`](https://www.lcsc.com/product-detail/Microcontroller-Units-MCUs-MPUs-SOCs_WCH-Jiangsu-Qin-Heng-CH32V003F4P6-EVT-WCH-LinkE_C5236707.html))
    * Starter Kit includes WCH-LinkE Debugger
  * 6 pcs. female-female jumper wires
  * (optional) additional 1 pc. female-female jumper wire for LED demo
* Software
  * Linux OS or WSL installation
  * [Docker Engine](https://docs.docker.com/engine/install/debian/) (running within WSL if applicable)
  * VSCode [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension
  * (WSL only) [usbipd-win](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) (Windows *and* WSL parts installed!)

### Hardware Setup

* (optional) Connect the `LED1` and `PC3` pins on header `P2` using a female-female jumper wire
* Follow instructions from the [WCH-LinkE User Manual](http://www.wch-ic.com/downloads/WCH-LinkUserManual_PDF.html) for connecting the debugger to your EVT board.

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
  * On first launch, you may need to install some udev rules on your host machine. Copy the files to your workspace by running `setup-devcontainer` inside the container.
  * Re-open the workspace on your host and run the `install-rules` script inside the `.vscode/setup` folder.

        cd .vscode/setup
        sudo ./install-rules

  * Afterwards, restart the devcontainer.
* Upon prompt, select the "**\[unspecified\]**" CMake Kit. 
* Run "**CMake: Configure**"
* Build using "**CMake: Build [F7]**"

* Split the terminal tab using the `[|]`-Button or press `Ctrl + Shift + 5`. Then launch the serial monitor:

      cu -l /dev/ttyACM0 -s 115200

  **To close the connection later on, press ESC/ENTER, type `~.` (tilde, dot) and wait for 3 seconds.**

* Start debugging using "**Debug: Start Debugging [F5]**"
* Continue execution once the breakpoint in `main()` is reached.
* Type `?` in the serial monitor Terminal tab to show available commands.

## WCH-LinkE Firmware Update
A firmware update of the WCH-LinkE debug probe to version `v31` or newer may be necessary. Use the [WCH-LinkUtility](https://www.wch.cn/downloads/WCH-LinkUtility_ZIP.html) to perform an online update of the programmer, as described in section 6.2 "*WCH-LinkUtility Online Update*" of the [WCH-Link User Manual](https://www.wch.cn/downloads/WCH-LinkUserManual_PDF.html).

* Pry open the clear case of the WCH-LinkE using a small flat-head screwdriver
* Push and hold the "IAP" button and insert the debugger into a USB port
* Start the `WCH-LinkUtility.exe`
* Confirm installation of the required drivers
* Click the "Query Read-Write-Protect Status" button (Alt + F5)

If a firmware update is available, a pop-up window will appear, asking you to confirm the update.

## SOIC8 Pin Mapping and "un-bricking"
On the SOIC8 package `CH32V003J4M6`, the debug interface is multiplexed with USART1 data lines. In the default configuration, enabling the UART transmitter will block debugger access. To use both USART1 and the debug port, **un-comment the `USE_SOIC8_UART_REMAP`** macro definition in `hw_layer/hw_iodefs.h`. Use the following table for connecting the debug probe to the SOIC8 part:

|WCH-LinkE Pin|SOIC8 Pin|
|-|-|
|`3V3`|4 `VDD`|
|`GND`|2 `VSS`|
|`SWDIO`|8 `PD1/PD5/PD4` (*)|
|`TX`|8 `PD1/PD5/PD4` (*)|
|`RX`|1 `PD6`|

*) **Note:** *WCH-LinkE `TX` and `SWDIO` lines are connected to the same pin at the SOIC8 part!*

In order to use the USART pin, close the debug connection (OpenOCD) in software. This releases the SWDIO line to a high-impedance state.

### Un-bricking an SOIC8 part
If an SOIC8 part has been programmed without swapping the RX/TX lines, debugger access is no longer possible. A full chip reset is required.

Use the [WCH-LinkUtility](https://www.wch.cn/downloads/WCH-LinkUtility_ZIP.html) to perform a full chip reset:
* MCU Core: `RISC-V`
* Series: `CH32V00x`
* Target -> "Clear All Code-Flash-By Power Off"

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