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

  void setLed(int index, uint8_t r, uint8_t g, uint8_t b) {
    _leds[index] = CRGB(r, g, b);
  }

  void setLed(int index, CRGB color) {
    _leds[index] = color;
  }

  void setAllLeds(CRGB color) {
    _leds[LED_LEFT] = color;
    _leds[LED_RIGHT] = color;
  }

  void setAllLeds(uint8_t r, uint8_t g, uint8_t b) {
    _leds[LED_LEFT] = CRGB(r, g, b);
    _leds[LED_RIGHT] = CRGB(r, g, b);
  }

  void show() {
    FastLED.show();
  }

  void pickTemperatureColor(int temperature) {
    if (temperature < 0) {
      setAllLeds(LED_WHITE);
    } else if (temperature < 10) {
      setAllLeds(LED_BLUE);
    } else if (temperature < 20) {
      setAllLeds(LED_GREEN);
    } else if (temperature < 30) {
      setAllLeds(LED_YELLOW);
    } else if (temperature < 40) {
      setAllLeds(LED_ORANGE);
    } else {
      setAllLeds(LED_RED);
    }
    show();
  }

private:
  CRGB _leds[NUM_LEDS];
  LED() : _leds{ CRGB(0, 0, 0), CRGB(0, 0, 0) } {
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(_leds, NUM_LEDS);
    FastLED.setBrightness(255);
  }
  static LED* ptr_instance;
};

LED* LED::ptr_instance = nullptr;


///////////////////////////////////////////////
/// LED implementation
///////////////////////////////////////////////



#endif // _LED_H_