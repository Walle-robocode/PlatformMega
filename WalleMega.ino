
#include "main.h"

void timerIsr() {
  cli();
  headServo.tick();
  mp3->tick();
  sei();
}

void setup() {
  initAllPeriphery();
  greetingWalle();
  delay(2000);
}

void loop() {
  esp->handle();
  bluetooth->handle();
}

void initAllPeriphery() {
  randomSeed(analogRead(0));
  // start init indicator;
  leds->setAllLeds(LED_RED);
  leds->show();

  Serial.begin(9600);   // Default serial communication
  esp->begin();
  bluetooth->begin();
  mp3->begin(25); // 0 - 30 - volume

  lcd.init();
  lcd.backlight();

  headServo.attach(2);
  headServo.setSpeed(80);
  headServo.setAccel(0.5);

  Timer1.initialize(10000); // 10ms
  Timer1.attachInterrupt(timerIsr);

  dht.begin();
  pinMode(34, OUTPUT); // Front LED light init port

  // done init indicator;
  leds->setAllLeds(LED_GREEN);
  leds->show();
  DEBUG_LOG("Wall-e is ready.");
  delay(500);
}

void greetingWalle() {
  mp3->play(MP3_SOUND_INTRO);
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print("#");
    lcd.setCursor(i, 1);
    lcd.print("#");

    if (i % 3 == 0 && i != 15) headServo.setTargetDeg(random(110, 150));

    if (i == 15) headServo.setTargetDeg(130);

    leds->setAllLeds(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
    leds->show();
    delay(60);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Привiт! Я: ");
  lcd.setCursor(5, 1);
  lcd.print("Wall-e");
}
