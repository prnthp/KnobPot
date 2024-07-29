// ADC Range:
// OFF: 180 - 205
// 1: 280 - 300
// 2: 375 - 390
// 3: 1190 - 1300

#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup(){}
void loop(){}
#else

#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

uint8_t state = 0;
uint16_t pot = 0;

void setup() {
  // initialize control over the keyboard:
  Keyboard.begin();
  USB.begin();
  Serial.begin(115200);
}

void loop() {
  pot = analogRead(17);
  uint8_t next_state = 255;

  if (pot <= 205) {
    next_state = 0;
  } else if (pot >= 285 && pot <= 300) {
    next_state = 1;
  } else if (pot >= 374 && pot <= 390) {
    next_state = 2;
  } else if (pot >= 1190) {
    next_state = 3;
  }

  if (next_state != state && next_state != 255) {
    state = next_state;
    switch (state) {
      case 0:
        Keyboard.write(0xEA);
        break;
      case 1:
        Keyboard.write(0xE1);
        break;
      case 2:
        Keyboard.write(0xE2);
        break;
      case 3:
        Keyboard.write(0xE3);
        break;
    }
  }

  Serial.println(pot);
  delay(2);
}
#endif /* ARDUINO_USB_MODE */