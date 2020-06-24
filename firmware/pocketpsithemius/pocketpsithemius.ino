/*Copyright (c) 2020 Sublunar Psionics

Special Thanks to Slavko Andrejevic for providing the main framework of this
firmware and for technical support.

---- MIT License ----

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <OneButton.h>

#define btnA            0      // PA0 / Button A:
#define btnB            2      // PA1 / Button B:
#define btnC            1      // PA2 / Button C:
#define led_R           4      // PA4 / RED LED
#define led_G           5      // PA5 / GREEN LED
#define led_B           6      // PA6 / BLUE LED
#define uv_LED          3      // PA3 / UV LED
#define OPAMP           8      // PB2 / turns on the Op Amp circuit
#define ANALOG          7      // PA7 / Get analog
#define REG1            9      // PB1 / unconnected
#define REG2           10      // PB0 / unconnected

#define ON              HIGH
#define OFF             LOW

//---- BUTTONS ----

byte counterA         = 0;     // count push btnA:
byte counterB         = 0;     // count push btnB:
byte counterC         = 0;     // count push btnC:
bool enabled_btnAC    = true;  // Button A + C enabled or not
bool enabled_btnB     = true;  // Button B enabled or not

OneButton buttonA(btnA, true); // Button A setup
OneButton buttonB(btnB, true); // Button B setup
OneButton buttonC(btnC, true); // Button C setup

//---- LEDS ----

bool enabled_LED      = false; //turn on a tricolor LED
bool usePWM           = false; //use softPWM for more nuanced colors
bool disco            = false; // random colors

//---- TIMER ----

bool countDelay       = false; //are we counting ticks to time out the UV LEDs?
uint32_t oldTime      = millis();

//---- COLOR ----

struct COLOR { // Creating structure for colors
  byte r;
  byte g;
  byte b;
};
COLOR selectedColor   = { 0, 0, 0 };

//---- PLANETARY COLORS ----

COLOR white           = { 255 , 255 , 255 }; // Moon correspondence
COLOR orange          = { 255 , 128 ,   0 }; // Mercury correspondence
COLOR green           = {   0 , 255 ,   0 }; // Venus correspondence
COLOR yellow          = { 255 , 255 ,   0 }; // Sol correspondence
COLOR red             = { 255 ,   0 ,   0 }; // Mars correspondence
COLOR blue            = {   0 , 128 , 255 }; // Jupiter correspondence
COLOR purple          = { 128 ,   0 , 128 }; // Jupiter/Moon correspondence
COLOR indigo          = { 111 ,   0 , 255 }; // Saturn correspondence
COLOR grey            = {  40 ,  40 ,  40 }; // Saturn correspondence

//---- DEVICE SETUP ----
void setup() {

  // BUTTONS
  buttonA.attachClick(cycleColors);
  buttonA.attachLongPressStart(discoStart);
  buttonB.attachClick(ultraviolet);
  buttonB.attachLongPressStart(uvForever);
  buttonC.attachClick(opAmp);

  // LEDS
  pinMode(led_B, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(led_R, OUTPUT);
  offLeds();

  // UV LED
  pinMode(uv_LED, OUTPUT);
  digitalWrite(uv_LED, OFF);

  // OP AMP
  //pinMode(ANALOG, INPUT);
  pinMode(OPAMP, OUTPUT);
  digitalWrite(OPAMP, OFF);

}

//---- DEVICE LOOP ----
void loop() {

  buttonA.tick();
  buttonB.tick();
  buttonC.tick();
  showColor();

  // If enabled, turns UV LED off after 1min
  if ( countDelay == true && ((millis()-oldTime) > 60000)) {
    //Turn the UV LED off
    enabled_btnAC = true;
    digitalWrite(uv_LED, OFF);
    counterB = 0;
    countDelay = false;
  }

  if ( disco == true ) {
    enabled_LED = true;
    usePWM = false;
    selectedColor.r = rng();
    selectedColor.g = rng();
    selectedColor.b = rng();
    //digitalWrite(uv_LED, bitRead(rng(), 0));
    showColor();
    delay(rng());
  }
  
}

//---- FUNCTIONS ----

// turn all LEDs off
void offLeds() {
  analogWrite(led_R, 255);
  analogWrite(led_B, 255);
  analogWrite(led_G, 255);
}

// set a color
void setColor(COLOR paint, bool full = true) {
  //tricolor LED color
  selectedColor.r = paint.r;
  selectedColor.b = paint.b;
  selectedColor.g = paint.g;
  showColor();
}

// show the color or turn off
void showColor() { // 100% of color
  if (enabled_LED == true) {
      softPWM(led_R, selectedColor.r, 1);
      softPWM(led_B, selectedColor.b, 1);
      softPWM(led_G, selectedColor.g, 1);
  } else {
    offLeds();
  }
}

void discoStart() {
  if ( disco == true ) {
    disco = false;
    enabled_LED = false;
    //digitalWrite(uv_LED, OFF);
    counterA = 0;
  }
  else disco = true;
}

// used for button A to cycle through the colors
void cycleColors() {
  if ( disco == true) discoStart();
  if (enabled_btnAC == true) {
    counterA++;
    switch (counterA) {
      case 1:
        enabled_LED = true;
        setColor(white, true);
        break;
      case 2:
        usePWM = true;
        setColor(orange, true);
        break;
      case 3:
        usePWM = false;
        setColor(green, true);
        break;
      case 4:
        setColor(yellow, true);
        break;
      case 5:
        setColor(red, true);
        break;
      case 6:
        setColor(blue, true);
        break;
      case 7:
        usePWM = true;
        setColor(purple, true);
        break;
      case 8:
        setColor(indigo, true);
        break;
      case 9:
        setColor(grey, true);
        break;
      case 10:
        enabled_LED = false;
        counterA = 0;//TURN OFF
        break;
    }
  }
}

// used for button B to toggle the UV LEDs
void ultraviolet() {
  counterA = 0;
  if ( disco == true) discoStart();
  if (enabled_btnB == true) {
    counterB++;
    switch (counterB) {
      case 1:
        blinker(led_B, 500, 5);
        enabled_LED = false;
        enabled_btnAC = false;
        digitalWrite(uv_LED, ON);
        if ( countDelay == false ) {
          oldTime    = millis();
        }
        countDelay = true; // turn on delay counter in loop()
        break;
      case 2:
        enabled_btnAC = true;
        digitalWrite(uv_LED, OFF);
        counterB = 0;
        break;
    }
  }
}

// disable all buttons and keep UV light running forever
void uvForever() {
  blinker(led_B, 500, 5);
  blinker(led_B, 50, 10);
  enabled_btnB = false;
  enabled_btnAC = false;
  countDelay = false;
  digitalWrite(uv_LED, ON);
}

// used for button C to toggle the OP Amp
void opAmp() {
  if (enabled_btnAC == true) {
    counterC++;
    switch (counterC) {
      case 1:
        blinker(led_G, 50, 2);
        digitalWrite(OPAMP, ON);
        break;
      case 2:
        blinker(led_R, 50, 2);
        digitalWrite(OPAMP, OFF);
        counterC = 0;
        break;
    }
  }
}

// helper to blink a color
void blinker(byte pin, int len, byte rep) {
  byte counter = 1;
  while (counter <= rep) {
    analogWrite(pin, 0);
    delay(len);
    offLeds();
    delay(len);
    counter++;
  }
}

// software PWM function that fakes analog output
void softPWM(byte pin, byte freq, byte sp) {
  byte delay1 = 255 - freq;
  if (usePWM == true) {
    while (sp > 0) {
      digitalWrite(pin, LOW); //on
      delayMicroseconds(freq);
      digitalWrite(pin, HIGH); //off
      delayMicroseconds(delay1);
      sp--;
    }
  } else {
    analogWrite(pin, 255 - freq);
  }
}

byte rng() {
  int raw0, raw1;
  byte b0, b1, x, col, twoBytes[2], result;
  col = 0;
  while ( col <= 1 ) {
    raw0 = analogRead(REG1);
    raw1 = analogRead(REG2);
    b0 = lowByte(raw0);
    b1 = lowByte(raw1);
    x = b0 ^ b1;
    twoBytes[col] = x;
    col++;
  }
  result = (twoBytes[0]<<4)+twoBytes[1];
  return result;
}
