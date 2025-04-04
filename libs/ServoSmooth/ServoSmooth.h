/*
    ServoSmooth - библиотека для плавного управления сервоприводами
    Документация: https://alexgyver.ru/servosmooth/
    GitHub: https://github.com/GyverLibs/ServoSmooth
    Возможности:
    - Дополнение к стандартной библиотеке Servo
    - Настройка максимальной скорости сервопривода
    - Настройка ускорения (разгон и торможение) сервопривода
    - Неблокирующая работа
    - Трапецеидальный профиль скорости
    - При использовании ESC и БК мотора получаем "плавный пуск" мотора
    - Устанвока целевой позиции серво по углу (0-180) и длине импульса (500-2400)
    - Автоматическое отключение (detach) при достижении цели
    - Плавный пуск при подключении серво
    - Поддержка расширителя PCA9685

    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.1 - автоматическое отключение (detach) при достижении цели
    v1.2 - вкл/выкл автоотключения серво
    v1.3 - отдельный метод для установки и чтения текущего положения. Добавлен вариант метода attach
    v1.4 - улучшена совместимость
    v1.5 - исправлены getCurrent и getCurrentDeg
    v1.6 - чуть оптимизирована инициализация
    v1.7 - исправлен баг с низкой скоростью/ускорением, код оптимизирован
    v1.8 - улучшена стабильность
    v1.9 - добавлена настройка макс. угла серво
    v1.10 - исправлен баг когда текущая позиция совпадает с позицией таргета

    v2.0 - упрощён алгоритм
    v2.1 - добавлена смена направления
    v2.2 - фикс движения в инверсии (спасибо VICLER) и функций write (спасибо CheDima)

    v3.0
    - Добавлен полностью новый, более плавный алгоритм
    - Почищен мусор
    - Добавлена поддержка PCA9685
    - "Плавность" вынесена в базовый класс для упрощения добавления поддержки новых библиотек серво

    v3.1 - оптимизирован и облегчён алгоритм, скорость задаётся в градусах/сек
    v3.2 - исправлен баг с резким поворотом при первом tick, добавлена smoothStart
    v3.3 - исправлен баг, возникающий если не вызывать tick
    v3.4 - при установке ускорения в 0 активируется профиль постоянной скорости

    v3.5
    - Улучшена/исправлена работа stop
    - Поправлены ошибки с округлением
    - Исправлена проблема с медленным изменением target

    v3.6 - Исправлены мелкие баги, вырезан дебаг с 3.5
    v3.7 - Добавлено задание ускорения в градусах/сек/сек
    v3.8 - Исправлен невозврат тика при autoDetach(false)
    v3.9 - поддержка ESP32
*/

#ifndef _ServoSmooth_h
#define _ServoSmooth_h
#include <Arduino.h>
#if defined(ESP32)
#include <ESP32Servo.h>
#else
#include <Servo_Hardware_PWM.h>
#endif
#include "smoothUtil.cpp"

#define _SERVO_DEADZONE 10      // мёртвая зона (по микросекундам)
#define _SERVO_DEADZONE_SP 3    // мёртвая зона (по скорости)

class ServoSmooth : public Smooth {
public:
    ServoSmooth(int maxAngle = 180);
    using Smooth::attach;
    void attach(int pin);
    void detach();
    void sendToDriver(uint16_t val);
    Servo _servo;
private:
};
#endif