#include "Display.h"


Display::Display(uint8_t _enable, uint8_t _clock, uint8_t _data) {
  enable_pin = _enable;
  clock_pin = _clock;
  data_pin = _data;

  // # Почему таблица не статичная??
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

  charValue['A'] = (uint8_t)Letters::Letter_A;
  charValue['B'] = (uint8_t)Letters::Letter_B;
  charValue['C'] = (uint8_t)Letters::Letter_C;
  charValue['D'] = (uint8_t)Letters::Letter_D;
  charValue['E'] = (uint8_t)Letters::Letter_E;
  charValue['F'] = (uint8_t)Letters::Letter_F;
  charValue['G'] = (uint8_t)Letters::Letter_G;
  charValue['H'] = (uint8_t)Letters::Letter_H;
  charValue['I'] = (uint8_t)Letters::Letter_I;
  charValue['J'] = (uint8_t)Letters::Letter_J;
  charValue['K'] = (uint8_t)Letters::Letter_K;
  charValue['L'] = (uint8_t)Letters::Letter_L;
  charValue['M'] = (uint8_t)Letters::Letter_M;
  charValue['N'] = (uint8_t)Letters::Letter_N;
  charValue['O'] = (uint8_t)Letters::Letter_O;
  charValue['P'] = (uint8_t)Letters::Letter_P;
  charValue['R'] = (uint8_t)Letters::Letter_R;
  charValue['S'] = (uint8_t)Letters::Letter_S;
  charValue['T'] = (uint8_t)Letters::Letter_T;
  charValue['U'] = (uint8_t)Letters::Letter_U;
  charValue['V'] = (uint8_t)Letters::Letter_V;
  charValue['W'] = (uint8_t)Letters::Letter_W;
  charValue['X'] = (uint8_t)Letters::Letter_X;
  charValue['Y'] = (uint8_t)Letters::Letter_Y;
  charValue['Z'] = (uint8_t)Letters::Letter_Z;
  charValue[' '] = (uint8_t)Letters::_Space;

  charValue['-'] = (uint8_t)Special::_Minus;
}


void Display::setup() {
  pinMode(enable_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  cls();
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

// # перегруженная функция которая в разных перегрузках работает с разными слоями логики
// этот принт работает непосредственно с электроникой и сигналами
// другой принт подготавливает данные и печатает их
// 
// так же есть проблема с частым вызовом printCurrentState который вызывается после каждого обновления
// а если я хочу обновить 2 строки из 3х
//    -> 2 принта
//    -> либо получения одной из строк и вызов print(a,old_b,c)
//
// как вариант разбить обновления дисплея и отрисовку
//    Dispalay& updateRow(int id,const char * str) // ссылка позволит чэйнить вызовы
//    void (flush/display/print)() // отправить текущее состояние на дисплей
//    так же таким дизайном можно уменьшить количество вызовов translate отлаживая вызов до момента flush
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

// # очепятка
void Display::wipeSate(uint8_t i) {
  // # дублирование кода из за решения хранить row раздельно
  // можно было остановиться на коде вида
  // uint8_t* rows[3] = [row1,row2,row3]
  // size_t row_slots = [FIRST_ROW_SLOTS,SECOND_ROW_SLOTS,THIRD_ROW_SLOTS]
  // индерекция не так сильно влияет на производительность как другие косяки в коде этого проекта
  if (i == 0) str1[0] = '\0';
  if (i == 1) str2[0] = '\0';
  if (i == 2) str3[0] = '\0';

  // # memset u know??
  if (i == 0) for (size_t i = 0; i < FIRST_ROW_SLOTS; ++i) row1[i] = Letters::_Space;
  if (i == 1) for (size_t i = 0; i < SECOND_ROW_SLOTS; ++i) row2[i] = Letters::_Space;
  if (i == 2) for (size_t i = 0; i < THIRD_ROW_SLOTS; ++i) row3[i] = Letters::_Space;
}


size_t Display::translate(const char* str, uint8_t* buf, size_t bufSize) {
  size_t it = 0;
  size_t strLen = 0;

  // # можно итерироваться по указателям 
  // по строке for(char * c = str;*c != '\0'; ++c)
  // и по buf, код станет немного проще читать

  // ## strlen внутри for, это сильно верить в компилятор
  // в худшем случае получшишь O(N*N)
  // в лучшем O(2 * N) вместо O(N)
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
  char rowFirst[12];

  size_t res1 = translate(firstRow, this->row1, FIRST_ROW_SLOTS);
  size_t res2 = translate(secondRow, this->row2, SECOND_ROW_SLOTS);
  size_t res3 = translate(thirdRow, this->row3, THIRD_ROW_SLOTS);

  memcpy(str1, firstRow, sizeof(char) * res1); str1[res1] = '\0';
  memcpy(str2, secondRow, sizeof(char) * res2); str2[res2] = '\0';
  memcpy(str3, thirdRow, sizeof(char) * res3); str3[res3] = '\0';

  printCurrentState();
}


// # неконсистенто отнистельно wipeState(int id)
void Display::printRow1(const char* str) {
  size_t res = translate(str, this->row1, FIRST_ROW_SLOTS);
  memcpy(str1, str, sizeof(char) * res); str1[res] = '\0';
  printCurrentState();
}


void Display::printRow2(const char* str) {
  size_t res = translate(str, this->row2, SECOND_ROW_SLOTS);
  memcpy(str2, str, sizeof(char) * res); str2[res] = '\0';
  printCurrentState();
}


void Display::printRow3(const char* str) {
  size_t res = translate(str, this->row3, THIRD_ROW_SLOTS);
  memcpy(str3, str, sizeof(char) * res); str3[res] = '\0';
  printCurrentState();
}


void Display::clearRow(uint8_t i) {
  wipeSate(i);
  printCurrentState();
}


// # можно заменить на геттер `const char * getStr1()` т.к. не каждому нужна копия данных для изменения
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