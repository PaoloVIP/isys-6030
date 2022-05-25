# Innosent iSYS-6030 - ESP32 sample code.

Innosent iSYS-6030 is a 60Ghz radar with very narrow FOV (6°) and a range up to 40 meters.
Please, read datasheet.

## Description

The code send start acquisition command, than reads the measures in single target mode.
A complete list of commands set can be found in API readme.

## Getting Started

* Connect GPIO 16 (RX) to TX Pin of ISYS-6030
* Connect GPIO 17 (TX) to RX Pin of iSYS-6030
+ Warning: when isys-6030 is in acquisition mode, can consumes, included ESP32, between 230 and 360mA at 5V. Using a good USB cable is therefore recommended.

### Dependencies

* #include <Arduino.h>

### Executing program

* Create a new project in your platformIO or Arduino IDE as usual.
* Copy this code, compile and upload to ESP32.

## Version History

* 0.1
    * Initial Release

## License

This project is licensed under the MIT License - see the LICENSE.md file for details


