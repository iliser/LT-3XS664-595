#include <Display.h>

Display::Display(uint8_t _enable, uint8_t _clock, uint8_t _data) {
  enable_pin = _enable;
  clock_pin = _clock;
  data_pin = _data;

  for (int i = 0; i < 128; ++i)
    charValue[i] = 0;
  charValue['0'] = (uint8_t)Digits::_0;
  charValue['1'] = (uint8_t)Digits::_1;
  charValue['2'] = (uint8_t)Digits::_2;
  charValue['3'] = (uint8_t)Digits::_3;
  charValue['4'] = (uint8_t)Digits::_4;
  charValue['5'] = (uint8_t)Digits::_5;
  charValue['6'] = (uint8_t)Digits::_6;
  charValue['7'] = (uint8_t)Digits::_7;
  charValue['8'] = (uint8_t)Digits::_8;
  charValue['9'] = (uint8_t)Digits::_9;

  charValue['A'] = (uint8_t)Letters::_A;
  charValue['B'] = (uint8_t)Letters::_B;
  charValue['C'] = (uint8_t)Letters::_C;
  charValue['D'] = (uint8_t)Letters::_D;
  charValue['E'] = (uint8_t)Letters::_E;
  charValue['F'] = (uint8_t)Letters::_F;
  charValue['G'] = (uint8_t)Letters::_G;
  charValue['H'] = (uint8_t)Letters::_H;
  charValue['I'] = (uint8_t)Letters::_I;
  charValue['J'] = (uint8_t)Letters::_J;
  charValue['K'] = (uint8_t)Letters::_K;
  charValue['L'] = (uint8_t)Letters::_L;
  charValue['M'] = (uint8_t)Letters::_M;
  charValue['N'] = (uint8_t)Letters::_N;
  charValue['O'] = (uint8_t)Letters::_O;
  charValue['P'] = (uint8_t)Letters::_P;
  charValue['R'] = (uint8_t)Letters::_R;
  charValue['S'] = (uint8_t)Letters::_S;
  charValue['T'] = (uint8_t)Letters::_T;
  charValue['U'] = (uint8_t)Letters::_U;
  charValue['V'] = (uint8_t)Letters::_V;
  charValue['W'] = (uint8_t)Letters::_W;
  charValue['X'] = (uint8_t)Letters::_X;
  charValue['Y'] = (uint8_t)Letters::_Y;
  charValue['Z'] = (uint8_t)Letters::_Z;
  charValue[' '] = (uint8_t)Letters::_Space;

  charValue['-'] = (uint8_t)Special::_Minus;

  wipeState();
}

void Display::setup() {
  pinMode(enable_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  clearLCD();
}

/* Clock signal generator */
void Display::generateCLK() {
  digitalWrite(clock_pin, LOW);
  digitalWrite(clock_pin, HIGH);
  digitalWrite(clock_pin, LOW);
}

/* Enable signal generator */
void Display::generateEnable() {
  digitalWrite(enable_pin, LOW);
  digitalWrite(enable_pin, HIGH);
  digitalWrite(enable_pin, LOW);
}

/* Set initial pins state */
void Display::init() {
  digitalWrite(enable_pin, HIGH);
  digitalWrite(clock_pin, LOW);
  digitalWrite(data_pin, LOW);
}


void Display::print(uint8_t charCode) {
  init();
  for (int i = 0; i < 8; ++i) {
    digitalWrite(this->data_pin, charCode & bit(i));
    generateCLK();
    generateEnable();
  }
  init();
}


void Display::cls() {
  wipeState();
  printCurrentState();
}

void Display::wipeState() {
  str1[0] = str2[0] = str3[0] = '\0';
  for (size_t i = 0; i < FIRST_ROW_SLOTS; ++i) row1[i] = Letters::_Space;
  for (size_t i = 0; i < SECOND_ROW_SLOTS; ++i) row2[i] = Letters::_Space;
  for (size_t i = 0; i < THIRD_ROW_SLOTS; ++i) row3[i] = Letters::_Space;
}

void Display::printCurrentState() {
  for (int i = THIRD_ROW_SLOTS - 1; i >= 0; --i) print(row3[i]);
  for (int i = SECOND_ROW_SLOTS - 1; i >= 0; --i) print(row2[i]);
  for (int i = FIRST_ROW_SLOTS - 1; i >= 0; --i) print(row1[i]);
}

void Display::wipeSate(uint8_t i) {
  if (i == 0) str1[0] = '\0';
  if (i == 1) str2[0] = '\0';
  if (i == 2) str3[0] = '\0';

  if (i == 0) for (size_t i = 0; i < FIRST_ROW_SLOTS; ++i) row1[i] = Letters::_Space;
  if (i == 1) for (size_t i = 0; i < SECOND_ROW_SLOTS; ++i) row2[i] = Letters::_Space;
  if (i == 2) for (size_t i = 0; i < THIRD_ROW_SLOTS; ++i) row3[i] = Letters::_Space;
}

size_t Display::translate(const char* str, uint8_t* buf, size_t bufSize) {
  size_t it = 0;
  size_t strLen = 0;
  for (size_t i = 0; i < strlen(str); ++i) {
    if (str[i] == '.' || str[i] == ',') {
      if (it) {
        bitClear(buf[it - 1], 0);
        ++strLen;
      }
      continue;
    }
    if (it == bufSize) break;
    buf[it] = charValue[toUpperCase(str[i])];
    ++strLen;
    ++it;
  }
  for (; it < bufSize; ++it)
    buf[it] = Letters::_Space;

  return strLen;
}

void Display::print(const char* firstRow, const char* secondRow, const char* thirdRow) {
  wipeState();
  size_t res1 = translate(firstRow, this->row1, FIRST_ROW_SLOTS);
  size_t res2 = translate(secondRow, this->row2, SECOND_ROW_SLOTS);
  size_t res3 = translate(thirdRow, this->row3, THIRD_ROW_SLOTS);

  memcpy(str1, firstRow, res1); str1[res1] = '\0';
  memcpy(str2, firstRow, res2); str2[res2] = '\0';
  memcpy(str3, firstRow, res3); str3[res3] = '\0';

  printCurrentState();
}

void Display::printFirstRow(const char* str) {
  size_t res = translate(str, this->row1, FIRST_ROW_SLOTS);
  memcpy(str1, str, res); str1[res] = '\0';
  showCurrentStrs();
  printCurrentState();
}

void Display::printSecondRow(const char* str) {
  size_t res = translate(str, this->row2, SECOND_ROW_SLOTS);
  memcpy(str2, str, res); str2[res] = '\0';
  showCurrentStrs();
  printCurrentState();
}

void Display::printThirdRow(const char* str) {
  size_t res = translate(str, this->row3, THIRD_ROW_SLOTS);
  memcpy(str3, str, res); str3[res] = '\0';
  showCurrentStrs();
  printCurrentState();
}

void Display::clearRow(uint8_t i) {
  wipeSate(i);
  printCurrentState();
}

void Display::getStrState(char* r1, char* r2, char* r3) {
  for (int i = 0; i < FIRST_STR_LEN; ++i) r1[i] = str1[i];
  for (int i = 0; i < SECOND_STR_LEN; ++i) r2[i] = str2[i];
  for (int i = 0; i < THIRD_STR_LEN; ++i) r3[i] = str3[i];
}

void Display::getStrState1(char* r) {
  for (int i = 0; i < FIRST_STR_LEN; ++i) r[i] = str1[i];
  r[FIRST_STR_LEN] = '\0';
}

void Display::getStrState2(char* r) {
  for (int i = 0; i < SECOND_STR_LEN; ++i) r[i] = str2[i];
  r[SECOND_STR_LEN] = '\0';
}

void Display::getStrState3(char* r) {
  for (int i = 0; i < THIRD_STR_LEN; ++i) r[i] = str3[i];
  r[THIRD_STR_LEN] = '\0';
}