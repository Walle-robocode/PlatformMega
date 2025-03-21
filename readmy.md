[![Platform](https://img.shields.io/badge/Platform-ARDUINO-blue.svg)](https://www.arduino.cc)
[![Language](https://img.shields.io/badge/lang-C++-blue.svg)](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers)
[![Company](https://img.shields.io/badge/-ROBOCODE-blue.svg)](https://robocode.ua)
[![CPU](https://img.shields.io/badge/CPU-MEGA2560-blue.svg)](https://docs.arduino.cc/hardware/mega-2560/)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/Walle-robocode/PlatformMega)

## WALL-E ROBOCODE MEGA2560 Platform



### Description:
___
This project aims to improve the performance of the Wall-e robot platform from **`ROBOCODE`**. This particular part of the code is responsible for the mechanical platform, including motor control, headlights, display, servo, sound module, and more. The updated code works only with the updated code for the ESP32 module, so both controllers need to be reprogrammed. It also relies on the updated audio recording library, which is located in a separate repository.
___

In general, Wall-e from **`ROBOCODE`** is a demonstration robot used to entertain students during breaks and to showcase the capabilities of small robotic platforms based on ARDUINO.

Give a ⭐ if you like the project.

### Hardware compatible
___

This code is designed exclusively for use with the Wall-e platform from **`ROBOCODE`**. The platform is based on the AtMega2560 controller with the ARDUINO MEGA bootloader, allowing you to customize the code for your project if necessary.

**Hardware components:**

- MCU - **AtMega2560** (Arduino Mega)
- USB -> UART module - **CH340G** (for PC connection and flashing)
- Bluetooth **HC-05**
- SD Player - **DFPlayer**
- Amplifier - **PAM8302A** module
- Temperature sensor - **DHT22**
- LCD - **16x2 I2C**

**Libraries:**

- FastLED 3.7.1
- LiquidCrystal_I2C
- TimerOne 1.1.1
- Adafruit Unified Sensor 1.0.3
- DHT sensor library 1.4.2
- DFRobotDFPlayerMini 1.0.6

### Installations
___

You will need the Arduino IDE on your computer. The project was created in the Visual Code environment with the Arduino Community Edition extension. However, everything should work in the regular Arduino IDE.

You need to download the source code to your PC, unpack it, and open the `WalleMega.ino` file in the Arduino IDE. Then you need to install all the libraries listed above.

If everything is done correctly, there should be no errors after clicking `Verify/Compile`. If errors occur, check the installed libraries and their versions.

If everything compiles without errors, you can connect the robot via USB and upload the code. Note that the robot has an `ESP / MEGA` switch on the back panel. To upload the code to the platform, move the slider to the `MEGA` position.

### How to Contribute:
___

Contributing to this software is warmly welcomed.
1. Test it, and if you find any problems, then post an issue.
2. Help us solve the issues or other bugs.