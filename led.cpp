#include "led.h"


LED* LED::ptr_instance = nullptr;

LED::LED() : _leds{ CRGB(0, 0, 0), CRGB(0, 0, 0) } {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(_leds, NUM_LEDS);
  FastLED.setBrightness(255);
}

void  LED::setLed(int index, uint8_t r, uint8_t g, uint8_t b) {
  _leds[index] = CRGB(r, g, b);
}

void LED::setLed(int index, CRGB color) {
  _leds[index] = color;
}

void LED::setAllLeds(CRGB color) {
  _leds[LED_LEFT] = color;
  _leds[LED_RIGHT] = color;
}

void LED::setAllLeds(uint8_t r, uint8_t g, uint8_t b) {
  _leds[LED_LEFT] = CRGB(r, g, b);
  _leds[LED_RIGHT] = CRGB(r, g, b);
}

void LED::show() {
  FastLED.show();
}

void LED::pickTemperatureColor(int temperature) {
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