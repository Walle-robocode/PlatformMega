#include "mp3.h"

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

void MP3::sayNumber(int num) {
  int num1 = 0;
  int num2 = 0;
  if (num < 20) {
    num2 = num;
  } else {
    num2 = num % 10;
    num1 = num / 10;
  }
  if (num1 != 0) {
    DFRobotDFPlayerMini::playFolder(2, num1 * 10);
    delay(700);
  }
  DFRobotDFPlayerMini::playFolder(2, num2);
  delay(900);
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