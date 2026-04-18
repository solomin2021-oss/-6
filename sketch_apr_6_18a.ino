#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(0x27, 16, 2);  // присваиваем имя дисплею

// Переменные для хранения времени
int hours = 18;      // начальные часы
int minutes = 30;    // начальные минуты
int seconds = 0;     // начальные секунды
int day = 12;        // день
int month = 6;       // месяц
int year = 20;       // год (2020)
int weekday = 5;     // день недели (5 = четверг)

unsigned long previousMillis = 0;  // для хранения предыдущего времени

// Массив названий дней недели
const char* weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup() {
  delay(300);
  LCD.init();           // инициализация LCD дисплея
  LCD.backlight();      // включение подсветки дисплея
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Обновляем каждую секунду
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    
    // Увеличиваем секунды
    seconds++;
    
    // Обновляем минуты
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      
      // Обновляем часы
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        
        // Обновляем день
        if (hours >= 24) {
          hours = 0;
          day++;
          
          // Простая проверка дней в месяце (без учета високосных годов)
          int daysInMonth = 31;
          if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
          } else if (month == 2) {
            daysInMonth = 28;  // февраль (без високосного года)
          }
          
          if (day > daysInMonth) {
            day = 1;
            month++;
            
            if (month > 12) {
              month = 1;
              year++;
            }
          }
          
          // Обновляем день недели
          weekday++;
          if (weekday > 7) {
            weekday = 1;
          }
        }
      }
    }
    
    // Выводим время на дисплей
    LCD.setCursor(0, 0);
    // Форматируем дату: "DD MM YYYY, DDD"
    LCD.print(day);
    LCD.print(" ");
    LCD.print(month);
    LCD.print(" ");
    LCD.print(2000 + year);  // добавляем 2000 для полного года
    LCD.print(", ");
    LCD.print(weekdays[weekday - 1]);
    
    // Добавляем пробелы для очистки старых символов
    LCD.print("   ");
    
    LCD.setCursor(4, 1);
    // Форматируем время: "HH:MM:SS"
    if (hours < 10) LCD.print("0");
    LCD.print(hours);
    LCD.print(":");
    if (minutes < 10) LCD.print("0");
    LCD.print(minutes);
    LCD.print(":");
    if (seconds < 10) LCD.print("0");
    LCD.print(seconds);
    
    // Добавляем пробелы для очистки
    LCD.print("   ");
  }
}