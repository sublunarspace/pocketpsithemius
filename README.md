# pocketpsithemius

Firmware for the Pocket Psithemius device.

## About the Pocket Psithemius

The "Pocket Psithemius" is a so-called "Table of Practice", a tool for spirit communication and manifestation. Its design is based on instructions found in an early 19th century book on ceremonial magic called "The Magus" by Francis Barrett. 

Written in 1801 in the middle of the 'Age of Reason', sandwiched between Newton and Darwin, this work embodies deep knowledge of Alchemy, Astrology, and the Kabbalah. The heavily plagiarized book features a treatise called "The Art of Drawing Spirits Into Crystals" that is attributed to the late Renaissance abbott and magician Johannes Trithemius von Spanheim, who famously invented a system of cryptography named "steganography." 

Part of the instruction for building a set of tools that will allow the operator to conjure and communicate with spirits, is a circular "Table of Practice" that features a "Triangle of Manifestation". The Psithemius uses a simplified design and electronic improvements from the 20th century fringe science of "radionics" to establish and amplify a communication link between the operator and discarnate entities and for manifesting magical will. The device does not work by itself without proper ritual framework.

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