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

enum Digits {
  _0 = 0b11111101,
  _1 = 0b01100001,
  _2 = 0b11011011,
  _3 = 0b11110011,
  _4 = 0b01100111,
  _5 = 0b10110111,
  _6 = 0b10111111,
  _7 = 0b11100001,
  _8 = 0b11111111,
  _9 = 0b11110111,
};

// TODO: Upper/Lower case
enum Letters {
  _A = 0b11101111,
  _B = 0b00111111,
  _C = 0b10011101,
  _D = 0b01111011,
  _E = 0b10011111,
  _F = 0b10001111,
  _G = 0b10111101,
  _H = 0b01101111,
  _I = 0b00001101,
  _j = 0b10110001,
  _J = 0b01111001,
  _K = 0b10101111,
  _L = 0b00011101,
  _M = 0b10101011,
  _N = 0b11101101,
  _O = 0b11111101,
  _P = 0b11001111,
  _Q = 0b11100111,
  _R = 0b00001011,
  _S = 0b10110111,
  _T = 0b00011111,
  _U = 0b01111101,
  _V = 0b01111101,
  _W = 0b01010111,
  _X = 0b01101111,
  _Y = 0b01110111,
  _Z = 0b01100001,
  _Space = 0b00000001,
};

enum Cyrillic {
  _cA = Letters::_A,
  _cB = Digits::_6,
  _cV = 0b11111111,
  _cG = 0b10001101,
  _cD = Letters::_D,
  _cYe = Letters::_E,
  _cZ = Digits::_3,
  _cI = 0b01101101,
  _cK = Letters::_K,
  _cL = Letters::_N,
  _cM = Letters::_M,
  _cN = Letters::_H,
  _cO = Letters::_O,
  _cP = Letters::_N,
  _cR = Letters::_P,
  _cS = Letters::_C,
  _cT = Letters::_T,
  _cU = 0b01110111,
  _cH = Letters::_X,
  _cTs = Letters::_U,
  _cCh = Digits::_4,
  _cE = Digits::_3,
  _cYa = 0b11101111,

  _c0 = 0b11111111,
  _cY = Letters::_Y,
};

enum Special {
  _Minus = 0b00000011,
};

class Display {
public:
  Display(uint8_t _enable, uint8_t _clock, uint8_t _data);
  int enable_pin;
  int clock_pin;
  int data_pin;
  void print(const char* firstRow, const char* secondRow, const char* thirdRow);
  void clearLCD();

  void printFirstRow(const char* str);
  void printSecondRow(const char* str);
  void printThirdRow(const char* str);

  void clearRow(uint8_t i);

  void setup();

  uint8_t* getState1();
  uint8_t* getState2();
  uint8_t* getState3();

  void setState1(uint8_t* buf);
  void setState2(uint8_t* buf);
  void setState3(uint8_t* buf);

protected:
  void translate(const char* str, uint8_t* buf, size_t bufSize);
  void print(uint8_t charCode);
  static const uint8_t FIRST_ROW_SLOTS = 6;
  static const uint8_t SECOND_ROW_SLOTS = 6;
  static const uint8_t THIRD_ROW_SLOTS = 4;
  static const uint8_t LCD_SLOTS =
    FIRST_ROW_SLOTS + SECOND_ROW_SLOTS + THIRD_ROW_SLOTS;
  uint8_t charValue[128];

  inline void generateEnable() __attribute__((always_inline));
  inline void generateCLK() __attribute__((always_inline));
  inline void init() __attribute__((always_inline));

private:
  void printCurrentState();
  uint8_t row1[FIRST_ROW_SLOTS];
  uint8_t row2[SECOND_ROW_SLOTS];
  uint8_t row3[THIRD_ROW_SLOTS];
  inline void wipeState() __attribute__((always_inline));
  void wipeSate(uint8_t i);
};
#endif
