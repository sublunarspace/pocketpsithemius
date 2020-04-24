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

#define btnA    9 //PB0 / Button A:
#define btnB    8 //PB1 / Button B:
#define btnC   13 //PA7 / Button C:
#define led_R  12 //PA6 / RED LED
#define led_G  14 //PA3 / GREEN LED
#define led_B   1 //PA1 / BLUE LED
#define uv_LED  6 //PB3 / UV LED
#define OPAMP   3 //PB6 / turns on the Op Amp circuit
#define ON      HIGH
#define OFF     LOW

//---- BUTTONS ----
byte counterA         = 0; //count push btnA:
byte counterB         = 0; //count push btnB:
byte counterC         = 0; //count push btnC:
bool enabled_btnAC    = true;  //Button A + C enabled or not
bool enabled_btnB     = true;  //Button B enabled or not
static bool last_btnA = false; //Previous state of button A
static bool last_btnB = false; //Previous state of button B
static bool last_btnC = false; //Previous state of button C

//---- LEDS ----
bool enabled_LED = false; //turn on a tricolor LED
bool was_on_LED  = false; //was LED on?
bool usePWM      = false; //use softPWM for more nuanced colors
void offLeds() {
  analogWrite(led_R, 255);
  analogWrite(led_B, 255);
  analogWrite(led_G, 255);
}

//---- TIMER ----
bool countDelay            = false; //are we counting ticks to time out the UV LEDs?
static uint32_t delayCount = 0;
long lastDebounceTime      = 0;  // the last time the output pin was toggled
long debounceDelay         = 50; // the debounce time; increase if the output flickers

//---- COLOR ----
struct COLOR { //Creating structure for colors
  byte r;
  byte g;
  byte b;
};
COLOR selectedColor = { 0   ,   0 ,   0 };

void setColor(COLOR paint, bool full = true) {
  //tricolor LED color
  selectedColor = paint;
  selectedColor.r = paint.r;
  selectedColor.b = paint.b;
  selectedColor.g = paint.g;
  //paint contains r g b value for pwm on pins
  showColor();
}

void showColor() {
  if (enabled_LED == true) {
    softPWM(led_R, selectedColor.r, 1);
    softPWM(led_B, selectedColor.b, 1);
    softPWM(led_G, selectedColor.g, 1);
  } else {
    offLeds();
  }
}

//---- PLANETARY COLORS ----
COLOR white         = { 255 , 255 , 255 }; //Moon correspondence
COLOR orange        = { 255 , 128 ,   0 }; //Mercury correspondence
COLOR green         = {   0 , 255 ,   0 }; //Venus correspondence
COLOR yellow        = { 255 , 255 ,   0 }; //Sol correspondence
COLOR red           = { 255 ,   0 ,   0 }; //Mars correspondence
COLOR blue          = {   0 , 128 , 255 }; //Jupiter correspondence
COLOR purple        = { 128 ,   0 , 128 }; //Jupiter/Moon correspondence
COLOR indigo        = { 111 ,   0 , 255 }; //Saturn correspondence
COLOR grey          = {  40 ,  40 ,  40 }; //Saturn correspondence

//---- DEVICE SETUP ----
void setup() {

  //Buttons
  pinMode(btnA, INPUT);
  pinMode(btnB, INPUT);
  pinMode(btnC, INPUT);

  //LEDS
  pinMode(led_B, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(led_R, OUTPUT);
  offLeds();

  //UV LED
  pinMode(uv_LED, OUTPUT);
  digitalWrite(uv_LED, OFF);

  // OP AMP
  pinMode(OPAMP, OUTPUT);
  digitalWrite(OPAMP, OFF);
}

//---- DEVICE LOOP ----
void loop() {

  // Detect and debounce button presses
  if ( (millis() - lastDebounceTime) > debounceDelay) {
    
    //Button A:
    bool pressed_btnA = !digitalRead(btnA);
    if (pressed_btnA != last_btnA ) {
      if (pressed_btnA == true) {
        counterA++;
        if (counterA > 10)counterA = 1;
        pressButton_A();
      }
      last_btnA = pressed_btnA;
    }
  
    //Button B:
    bool pressed_btnB = !digitalRead(btnB);
    if (pressed_btnB != last_btnB ) {
      if (pressed_btnB == true) {
        counterB++;
        if (counterB > 2)counterB = 1;
        pressButton_B();
      }
      last_btnB = pressed_btnB;
    }
  
    //Button C:
    bool pressed_btnC = !digitalRead(btnC);
    if (pressed_btnC != last_btnC ) {
      if (pressed_btnC == true) {
        counterC++;
        if (counterC > 2)counterC = 1;
        pressButton_C();
      }
      last_btnC = pressed_btnC;
    }
    lastDebounceTime = millis(); //set the current time
  }
  
  showColor();

  //Counts up and turns UV LED off after 1min
  if (countDelay == true) {
    delayCount++;
    counterB = 1;
  }
  else delayCount = 0;
  if (delayCount > 1200000) {
    //Turn the UV LED off
    digitalWrite(uv_LED, LOW);
    countDelay = false;
    //Reenable all buttons
    enabled_btnAC = true;
    //LED Status back to before Button B was pushed
    enabled_LED = was_on_LED;
  }
}

//---- BUTTON STATE MACHINE FUNCTIONS
//Button A:
void pressButton_A() {
  if (enabled_btnAC == false) {
    counterA = 0;
    return;//Chek if button is disabled
  }
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

//Button B:
void pressButton_B() {
  if (enabled_btnB == false) {
    counterB = 0;
    return;
  }
  if (counterB == 1) { //1st press:
    //was color LED on when button was pushed?
    was_on_LED = enabled_LED;
    //Disable LED and buttons A and C
    enabled_LED = false;
    counterA = 0;
    counterC = 0;
    enabled_btnAC = false;
    enabled_btnB == false;
    //Turn off Op-Amp circuit
    digitalWrite(OPAMP, OFF);
    enabled_btnB == true;
    digitalWrite(uv_LED, ON);
    countDelay = true; // turn on delay counter in loop()
  }
  if (counterB == 2) { //2nd press:
    if (digitalRead(uv_LED) == ON) {
      //Turn UV LED off
      digitalWrite(uv_LED, OFF);
    }
    //Re-enable all buttons
    enabled_btnAC = true;
    enabled_btnB = true;
    //LED Status back to before Button B was pushed
    enabled_LED = was_on_LED;
    //reset delay counter
    countDelay = false;
  }
}

//Button C:
void pressButton_C() {
  if (enabled_btnAC == false) {
    counterC = 0;
    return;
  }
  if (counterC == 1) { //1st press:
    digitalWrite(OPAMP, ON);
  }
  if (counterC == 2) { //2nd press:
    digitalWrite(OPAMP, OFF);
  }
}

//---- SOFTWARE PWM ----
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
