#ifndef _MP3_H_
#define _MP3_H_

#include <Arduino.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "utils.h"

#define MP3Com Serial1

#define MP3_SOUND_INTRO 0
#define MP3_SOUND_DEGREE_BY_CELSIY 1
#define MP3_SOUND_DEGREE_BY_CELSIUS 2
#define MP3_SOUND_DEGREES_BY_CELSIUS 3
#define MP3_SOUND_AROUND_TEMPERATURE 4
#define MP3_SOUND_MAY_TYPE_ON_THE_DISPLAY 5
#define MP3_SOUND_TYPING_SONG 6

#define MP3_SOUND_ROBOCODE_POWER_SONG 7
#define MP3_SOUND_WHO_I_AM_SOUND 8
#define MP3_SOUND_TIRED_SOUND 9
#define MP3_SOUND_HA_HA_JOKE 10
#define MP3_SOUND_WALL_E_VOICE 11
#define MP3_SOUND_LEAVE_YOU_HANDS 12

const uint8_t PROGMEM sounds[][2] = {
  {1, 1}, // 0 Intro  0001.mp3
  {1, 2}, // 1 degree by celsiy 0002.mp3
  {1, 3}, // 2 degree by celsius 0003.mp3
  {1, 4}, // 3 degrees by celsius 0004.mp3
  {1, 5}, // 4 around temperature 0005.mp3
  {1, 6}, // 5 may type on the display 0006.mp3
  {1, 7}, // 6 typing song  0007.mp3

  {3, 2}, // 7 robocode power song 0002.mp3
  {3, 3}, // 8 who I am sound 0003.mp3
  {3, 4}, // 9 tired sound 0004.mp3
  {3, 5}, // 10 ha ha, joke 0005.mp3
  {3, 6}, // 11 wall-e voice 0006.mp3
  {3, 7}, // 12 leave you hands 0007.mp3
};



class MP3 : private DFRobotDFPlayerMini {
public:
  static MP3* getInstance() {
    if (ptr_instance == nullptr) {
      ptr_instance = new MP3();
    }
    return ptr_instance;
  }
  MP3(MP3 const&) = delete;
  void begin(uint8_t volume = 10);
  void tick();

  void play(uint8_t song);
  void sayNumber(int);


private:
  static MP3* ptr_instance;
  MP3();

  void _printDetails(uint8_t, int);
};

#endif // _MP3_H_