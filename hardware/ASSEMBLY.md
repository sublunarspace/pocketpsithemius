- [Assembling the DIY Psithemius](#assembling-the-diy-psithemius)
  * [1. Resistors](#1-resistors)
  * [2. Unpolarized Capacitors](#2-unpolarized-capacitors)
  * [3. Integrated Circuit Chips](#3-integrated-circuit-chips)
  * [4. Power Switch & Special Resistors](#4-power-switch---special-resistors)
  * [5. Rear Connectors](#5-rear-connectors)
  * [6. Polarized Capacitors](#6-polarized-capacitors)
  * [7. UV LEDs](#7-uv-leds)
  * [8. Buttons & Extra Connectors](#8-buttons---extra-connectors)
  * [9. Mechanical Assembly](#9-mechanical-assembly)
  * [10. Finalizing](#10-finalizing)
- [Troubleshooting](#troubleshooting)

# Assembling the DIY Psithemius

I usually start with the lowest profile components and work up to the highest. This guide follows my order of assembly.

## 1. Resistors

Identify the carbon film resistors using the color coding and stick them through the footprints of the PCB.

| Reference | Quantity | Value | Color Code | 
|-----------|----------|-------|------------|
|R1-R4, R7  |         5|   10KΩ|[brown, black, orange, gold](components/10k-ohm-resistor-color-code.jpg)|
|R5         |         1|    10Ω|[brown, black, black, gold](components/10-ohm-resistor-color-code.jpg)|
|R6, R11, R15|        3|   180Ω|[brown, grey, brown, gold](components/180-ohm-resistor-color-code.jpg)|
|R8-R10     |         3|   680Ω|[blue, grey, brown, gold](components/680-ohm-resistor-color-code.jpg)|
|R12-R14    |         3|   330Ω|[orange, orange, brown, gold](components/330-ohm-resistor-color-code.jpg)|

Stick them in from the top of the PCB, turn the PCB around and lay it flat on a table. Solder the resistor leads to the through-holes and clip the excess off.

R16 is a large wirewound resistor. Do that one at [Step 4](#4-power-switch---special-resistors).

## 2. Unpolarized Capacitors

The next higher components are the unpolarized radial leaded multilayer ceramic capacitors. 

They are yellow andf have two equally long legs. There are three tiny ones (0.1uF) and one a bit bigger one (1uF).

Again, stick them in from the top of the PCB, turn the PCB around and lay it flat on a table. Solder the capacitor leads to the through-holes and clip the excess off.

Revision 11 of the Psithemius has three additional capacitor footprints C7, C8, C9 marked on the PCB. Just ignore them. They will remain empty.

## 3. Integrated Circuit Chips

Now, identify the four different ICs and stick them into their footprints from the top. For each IC make sure the tiny dot on the chip marking pin 1 is placed into the square plated through-hole marking pin 1. Be careful to not push too hard and avoid bending their legs. Turn the PCB around and lay it flat on a table. Solder all legs.

| Reference | Color | No. legs |
|-----------|-------|----------|
|U1         | black |        14|
|U2         | white |         8|
|U3         | white |         4|
|U4         | black |         8|


## 4. Power Switch & Special Resistors

Now proceed with the 6 legged power switch S1 . Make sure the switch points outward away from the PCB disk. Do the same with the three legged variable resistor VR1.

Now solder the wire wound resistor R16. It's a bit tricky to get it solidly fixed due to the thick leads and large through-holes. Use more solder than with the other parts. Clip of the excess leads when cooled down.

## 5. Rear Connectors

Proceed soldering the barrel jack power connector. Revision 11 of the PCBs have a tiny error and the tiny plastic cube that sticks out of the bottom of this component does not have a matching hole in the PCB. In order to make it fit the footprint you need to cut this tiny piece of plastic off with an excacto knife or simply melt it with your hot soldering iron so the bottom plastic surface of the component is flat. Revision 12 of the PCB does not require this fix.

Proceed with the 3.5mm 1/8" stereo audio mini jack. The revision 11 footprint of this component has too many through-holes. Just solder the ones that have legs sticking through and ignore the others.

Now solder the full metal grounding connector in between the audio jack and power jack. I usually place it into the through-holes, the hole pointing outwards away from the PCB, turn the PCB around and lay it flat on the table, then I make sure the component is parallel to the PCB and table and I use quite a lot of solder to fix it to the holes.

## 6. Polarized Capacitors

The polarized capacitors need to be placed onto their circular "half-moon" type footprints. Make sure the longer leg (anode) of each pol. capacitor goes into the squarish through-hole on the dark half of the footprint with the little + symbol next to it. The greyish area of the pol. capacitor should point to the bright side of the "half-moon" footprint. Push them all the way down onto the PCB, otherwise they will be too high.

## 7. UV LEDs

Now assemble the 3 UV LEDs by placing them into their footprints. Caution! The footprint logic for diodes is opposite from the polarized capacitors. Here, the shorter leg (cathode) of each LED needs to go into the square through-hole near the flattened part of the footprint.

ATTENTION: make sure to not place them all the way into the footprint but leave a few millimeters space. They need to be bent in a 45° angle towards the center of the triangle on the PCB after they have been soldered. Only stick the legs through so the tiny "stoppers" on the legs will still be above the top layer of the PCB. I usually stick the LED into the PCB, then poke the plastic rod of a q-tip through its legs between the "bulb" and the PCB. Turn around and solder, remove the q-tips and finally bend the "bulbs" so they point towards the center of the triangle.

## 8. Buttons & Extra Connectors

I usually finish with the three push-buttons. Carefully click them into their footprints and solder them. The three black caps click neatly on top of the switches.

If you want to be able to upgrade the firmware of the Psithemius or code your own firmware, you need to solder the 6 pin AVR connector to the front side of the PCB.

There will be a DIY battery add-on for the Psithemius. In order to connect it, there is already a footprint for the white horizontal battery connector behind the barrel jack power connector. ATTENTION: It needs to be soldered upside down! Stick it through the footprint from the bottom of the PCB and solder the four pins from the top.

## 9. Mechanical Assembly

Put the four 25mm M2.5 screws into the four holes of the top-plate of the Psithemius with the magical symbols. Carefully flip it upside down, so the tips of the screws are pointint up.

Place the four 9mm long black distance bolts onto the screws.

Now carefully stick the fully assembled PCB upside down onto the four screws until it firmly rests on the distance bolts. Make sure the three buttons go through the openings of the top-plate.

Place the four 7mm long black distance bolts onto the screws sticking through the PCB.

Now place the glossy black plexiglass disk onto the screws until it firmly rests on the distance bolts.

Finally place the four washers and nuts and tighten all screws. Stick the four adhesive rubber bumpers next to the nuts, so the device has feet.

## 10. Finalizing

Turn the assembled Psithemius around and make sure everything fits tightly. Plug the USB power cable into the barrel jack and try out all the buttons.

# Troubleshooting

* None of the buttons do anything!
  + Check the solder contacts of the barrel jack and the power switch

* The Psithemius blinks and occasionally turns off!
  + Check the solder contacts of the barrel jack and make sure the polarized capacitor behind the audio jack is placed in the correct direction.

* The UV LEDs don't work!
  + You probably soldered the LEDs in the wrong direction.