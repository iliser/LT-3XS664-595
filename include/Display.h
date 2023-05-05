/*********************************************************************
  7 segment display schema:
 ┌── a ──┐
 |       |
 f       b
 |       |
 ├── g ──┤
 |       |
 e       c
 |       |
 └── d ──┴── h

 a - high bit
 h - low bit

**********************************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H


#include "Arduino.h"
#include "SevenSegmentChars.h"

class Display {
public:
  Display(uint8_t _enable, uint8_t _clock, uint8_t _data);

  void print(const char* firstRow, const char* secondRow, const char* thirdRow);
  void cls();

  void printRow1(const char* str);
  void printRow2(const char* str);
  void printRow3(const char* str);

  void clearRow(uint8_t i);

  void setup();

  void getStrState(char* r1, char* r2, char* r3);
  void getStrState1(char* r);
  void getStrState2(char* r);
  void getStrState3(char* r);
protected:
  size_t translate(const char* str, uint8_t* buf, size_t bufSize);
  void print(uint8_t charCode);
  static const uint8_t FIRST_ROW_SLOTS = 6;
  static const uint8_t SECOND_ROW_SLOTS = 6;
  static const uint8_t THIRD_ROW_SLOTS = 4;
  static const uint8_t LCD_SLOTS = FIRST_ROW_SLOTS + SECOND_ROW_SLOTS + THIRD_ROW_SLOTS;
  static const uint8_t FIRST_STR_LEN = (FIRST_ROW_SLOTS << 1);
  static const uint8_t SECOND_STR_LEN = (SECOND_ROW_SLOTS << 1);
  static const uint8_t THIRD_STR_LEN = (THIRD_ROW_SLOTS << 1);
  uint8_t charValue[128];

  inline void generateEnable() __attribute__((always_inline));
  inline void generateCLK() __attribute__((always_inline));
  inline void init() __attribute__((always_inline));

private:
  int enable_pin;
  int clock_pin;
  int data_pin;
  void printCurrentState();
  uint8_t row1[FIRST_ROW_SLOTS];
  uint8_t row2[SECOND_ROW_SLOTS];
  uint8_t row3[THIRD_ROW_SLOTS];

  char str1[FIRST_STR_LEN];
  char str2[SECOND_STR_LEN];
  char str3[THIRD_STR_LEN];
  inline void wipeState() __attribute__((always_inline));
  void wipeSate(uint8_t i);
};
#endif
