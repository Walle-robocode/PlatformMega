#include "main.h"

char cmd;

void setup() {
  initAllPeriphery();
  greetingWalle();
  delay(2000);
}

void loop() {
  esp.handle();

  if (BT.available()) {
    cmd = BT.read();
    Serial.println(cmd);
    switch (cmd) {
    case 'S': motors.setMotorsSpeed(0, 0); break;
    case 'F': motors.setMotorsSpeed(leftSpeed, rightSpeed); break;
    case 'B': motors.setMotorsSpeed(-leftSpeed, -rightSpeed); break;
    case 'L': motors.setMotorsSpeed(-leftSpeed, rightSpeed); break;
    case 'R': motors.setMotorsSpeed(leftSpeed, -rightSpeed); break;
    case 'I': motors.setMotorsSpeed(leftSpeed, 0); break;
    case 'G': motors.setMotorsSpeed(0, rightSpeed); break;
    case 'H': motors.setMotorsSpeed(0, -rightSpeed); break;
    case 'J': motors.setMotorsSpeed(-leftSpeed, 0); break;
    case 'X': break;
    case 'x': break;
    case 'w': digitalWrite(34, LOW); break;
    case 'W': digitalWrite(34, HIGH); break;
    case 'u': break;
    case 'U': break;
    case 'v': {
      dfMp3.playFolderTrack16(1, 1);
      delay(700);
      for (int i = 0; i < 16; i++) {
        if (i % 3 == 0 && i != 15) {
          headServo.write(random(110, 150));
        }

        if (i == 15) {
          headServo.write(130);
        }

        leds[0] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        leds[1] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        FastLED.show();
        delay(60);
      }
      break;
    }
    case 'V': {
      dfMp3.playFolderTrack16(1, 1);
      delay(700);
      for (int i = 0; i < 16; i++) {
        if (i % 3 == 0 && i != 15) {
          headServo.write(random(110, 150));
        }

        if (i == 15) {
          headServo.write(130);
        }

        leds[0] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        leds[1] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        FastLED.show();
        delay(60);
      }
      break;
    }
    case '1':
      leftSpeed = map(1, 1, 10, 0, 255);
      rightSpeed = map(1, 1, 10, 0, 255);
      break;
    case '2':
      leftSpeed = map(2, 1, 10, 0, 255);
      rightSpeed = map(2, 1, 10, 0, 255);
      break;
    case '3':
      leftSpeed = map(3, 1, 10, 0, 255);
      rightSpeed = map(3, 1, 10, 0, 255);
      break;
    case '4':
      leftSpeed = map(4, 1, 10, 0, 255);
      rightSpeed = map(4, 1, 10, 0, 255);
      break;
    case '5':
      leftSpeed = map(5, 1, 10, 0, 255);
      rightSpeed = map(5, 1, 10, 0, 255);
      break;
    case '6':
      leftSpeed = map(6, 1, 10, 0, 255);
      rightSpeed = map(6, 1, 10, 0, 255);
      break;
    case '7':
      leftSpeed = map(7, 1, 10, 0, 255);
      rightSpeed = map(7, 1, 10, 0, 255);
      break;
    case '8':
      leftSpeed = map(8, 1, 10, 0, 255);
      rightSpeed = map(8, 1, 10, 0, 255);
      break;
    case '9':
      leftSpeed = map(9, 1, 10, 0, 255);
      rightSpeed = map(9, 1, 10, 0, 255);
      break;
    case 'q':
      leftSpeed = map(10, 1, 10, 0, 255);
      rightSpeed = map(10, 1, 10, 0, 255);
      break;
    default: break;
    }
  }
}

void humor() {
  dfMp3.playFolderTrack16(3, 4);
  delay(1500);
  for (int i = 0; i < 10; i++) {
    leds[0] = CRGB(0, 255 - random(0, 200), 0);
    leds[1] = CRGB(0, 255 - random(0, 200), 0);
    FastLED.show();
    delay(random(20, 100));
    leds[0] = CRGB(0, 0, 0);
    leds[1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(random(20, 100));
  }
  delay(2000);
  leds[0] = CRGB(255, 0, 0);
  leds[1] = CRGB(255, 0, 0);
  FastLED.show();
  delay(100);
  dfMp3.playFolderTrack16(3, 5);
  delay(2000);
}

void initAllPeriphery() {
  randomSeed(analogRead(0));
  Serial.begin(9600);   // Default serial communication
  MP3Com.begin(9600);   // MP3 module communication
  BT.begin(9600);       // Bluetooth module communication
  esp.begin();
  lcd.init();
  lcd.backlight();
  headServo.attach(2);
  delay(2000);
  dfMp3.begin();
  dfMp3.setVolume(25);
  dht.begin();
  pinMode(34, OUTPUT);

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.println("Wall-e is ready.");
}

void greetingWalle() {
  dfMp3.playFolderTrack16(1, 1);
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print("#");
    lcd.setCursor(i, 1);
    lcd.print("#");

    if (i % 3 == 0 && i != 15) {
      headServo.write(random(110, 150));
    }

    if (i == 15) {
      headServo.write(130);
    }

    leds[0] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
    leds[1] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
    FastLED.show();
    delay(60);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Привiт! Я: ");
  lcd.setCursor(5, 1);
  lcd.print("Wall-e");
}
