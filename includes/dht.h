#ifndef DHT_H_
#define DHT_H_

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4
#define DHTTYPE DHT22

class HTSensor : public DHT_Unified {
public:
  HTSensor() : DHT_Unified(DHTPIN, DHTTYPE) {}
  int getTemperature() {
    sensors_event_t event;
    temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      return -255;
    } else {
      return event.temperature;
    }
  }

  int getHumidity() {
    sensors_event_t event;
    humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      return -255;
    } else {
      return event.relative_humidity;
    }
  }
};

#endif // DHT_H_