#ifndef _LED_H_
#define _LED_H_

#include <FastLED.h>

#define NUM_LEDS 2
#define DATA_PIN 42

#define LED_LEFT 0
#define LED_RIGHT 1

#define LED_RED CRGB(255, 0, 0)
#define LED_GREEN CRGB(0, 255, 0)
#define LED_BLUE CRGB(0, 0, 255)
#define LED_WHITE CRGB(255, 255, 255)
#define LED_BLACK CRGB(0, 0, 0)
#define LED_YELLOW CRGB(255, 255, 0)
#define LED_ORANGE CRGB(255, 165, 0)
#define LED_PURPLE CRGB(128, 0, 128)
#define LED_CYAN CRGB(0, 255, 255)
#define LED_PINK CRGB(255, 192, 203)

#define LED_DEFAULT_COLOR LED_BLUE

class LED {
public:
  static LED* getInstance() {
    if (ptr_instance == nullptr) {
      ptr_instance = new LED();
    }
    return ptr_instance;
  }
  LED(LED const&) = delete;
  void operator=(LED const&) = delete;

  void setLed(int index, uint8_t r, uint8_t g, uint8_t b);
  void setLed(int index, CRGB color);

  void setAllLeds(CRGB color);
  void setAllLeds(uint8_t r, uint8_t g, uint8_t b);

  void show();

  void pickTemperatureColor(int temperature);
  void pickBatteryColor(int batteryLevel);

private:
  CRGB _leds[NUM_LEDS];
  LED();
  static LED* ptr_instance;
};




#endif // _LED_H_