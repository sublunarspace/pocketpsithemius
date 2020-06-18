# Pocket Psithemius

Firmware for the Pocket Psithemius device.

## Installation

* Set up an Arduino as ISP programmer following [this tutorial](https://www.arduino.cc/en/Tutorial/ArduinoISP) or use any other ICSP compatible programmer.
* The firmware depends on the [OneButton library](https://github.com/mathertel/OneButton) which you need to install with the IDE's Library Manager
* Connect the Pocket Psithemius via ICSP to the programmer.

### IDE Tools Settings

* Board: Attiny24/44/84
* Chip: Attiny84
* Clock: 8MHz (internal)
* B.O.D. Level: B.O.D. Disabled
* Save EEPROM: EEPROM retained
* Pin Mapping: clockwise
* LTO: Enabled
* millis()/micros(): Enabled