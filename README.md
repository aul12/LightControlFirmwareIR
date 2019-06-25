# LightControlFirmwareIR
Controlling the Led-Strip in my room via IR. 
This is an [Mbed](https://os.mbed.com/) project for the 
[Freescale (now NXP) FRDM-K64F](https://www.nxp.com/support/developer-resources/evaluation-and-development-boards/freedom-development-boards/mcu-boards/freedom-development-platform-for-kinetis-k64-k63-and-k24-mcus:FRDM-K64F)
development board. It opens a UDP server which forwards the received byte via Infrared, using the NEC-Protocol.

## How to use
### Prerequisites
 * GNU make
 * An ARM cross compiler (for example `arm-none-eabi-gcc`)
 
### Building and flashing
To build the programm just run the
```
make
```
command in the root directory of the repo, this should generate a file called `IrControllUDP.bin`.
After plugging in the K64F-Devboard copy the file to the board (the board show act as an USB-Storage-Device
