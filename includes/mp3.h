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
  void sayNumber(int number);


private:
  static MP3* ptr_instance;
  MP3();

  void _printDetails(uint8_t, int);
};


////////////////////////////////////////
// Implementation
////////////////////////////////////////

MP3* MP3::ptr_instance = nullptr;

MP3::MP3() : DFRobotDFPlayerMini() {}

void MP3::begin(uint8_t volume) {
  MP3Com.begin(9600);
  if (!DFRobotDFPlayerMini::begin(MP3Com, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin MP3 player:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  DEBUG_LOG("DFPlayer Mini online.");
  DFRobotDFPlayerMini::setTimeOut(500); //Set serial communication time out 500ms
  DFRobotDFPlayerMini::volume(volume);  //Set volume value (0~30).
  DFRobotDFPlayerMini::outputDevice(DFPLAYER_DEVICE_SD); //Set device we use SD as default.
  DEBUG_LOG("MP3 player is configured.");
}

void MP3::tick() {
  if (DFRobotDFPlayerMini::available()) {
    _printDetails(DFRobotDFPlayerMini::readType(), DFRobotDFPlayerMini::read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void MP3::play(uint8_t sound) {
  uint8_t folder = _RM(sounds[sound][0]);
  uint8_t track = _RM(sounds[sound][1]);
  Serial.print("Playing sound:");
  Serial.print(folder);
  Serial.println(track);
  DFRobotDFPlayerMini::playFolder(folder, track);
}

void MP3::sayNumber(int number) {
  if (number < 20) {
    DFRobotDFPlayerMini::playFolder(2, number);
  } else {
    int num1 = number / 10;
    int num2 = number % 10;
    DFRobotDFPlayerMini::playFolder(2, num1 * 10);
    delay(600);
    DFRobotDFPlayerMini::playFolder(2, num2);
    delay(700);
  }
}

void MP3::_printDetails(uint8_t type, int value) {
  switch (type) {
  case TimeOut:
    Serial.println(F("Time Out!"));
    break;
  case WrongStack:
    Serial.println(F("Stack Wrong!"));
    break;
  case DFPlayerCardInserted:
    Serial.println(F("Card Inserted!"));
    break;
  case DFPlayerCardRemoved:
    Serial.println(F("Card Removed!"));
    break;
  case DFPlayerCardOnline:
    Serial.println(F("Card Online!"));
    break;
  case DFPlayerUSBInserted:
    Serial.println("USB Inserted!");
    break;
  case DFPlayerUSBRemoved:
    Serial.println("USB Removed!");
    break;
  case DFPlayerPlayFinished:
    Serial.print(F("Number:"));
    Serial.print(value);
    Serial.println(F(" Play Finished!"));
    break;
  case DFPlayerError:
    Serial.print(F("DFPlayerError:"));
    switch (value) {
    case Busy:
      Serial.println(F("Card not found"));
      break;
    case Sleeping:
      Serial.println(F("Sleeping"));
      break;
    case SerialWrongStack:
      Serial.println(F("Get Wrong Stack"));
      break;
    case CheckSumNotMatch:
      Serial.println(F("Check Sum Not Match"));
      break;
    case FileIndexOut:
      Serial.println(F("File Index Out of Bound"));
      break;
    case FileMismatch:
      Serial.println(F("Cannot Find File"));
      break;
    case Advertise:
      Serial.println(F("In Advertise"));
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

#endif // _MP3_H_