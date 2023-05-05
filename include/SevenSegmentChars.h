#ifndef SEVEN_SEGMENT_CHARS
#define SEVEN_SEGMENT_CHARS

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
  Letter_A = 0b11101111,
  Letter_B = 0b00111111,
  Letter_C = 0b10011101,
  Letter_D = 0b01111011,
  Letter_E = 0b10011111,
  Letter_F = 0b10001111,
  Letter_G = 0b10111101,
  Letter_H = 0b01101111,
  Letter_I = 0b00001101,
  Letter_j = 0b10110001,
  Letter_J = 0b01111001,
  Letter_K = 0b10101111,
  Letter_L = 0b00011101,
  Letter_M = 0b10101011,
  Letter_N = 0b11101101,
  Letter_O = 0b11111101,
  Letter_P = 0b11001111,
  Letter_Q = 0b11100111,
  Letter_R = 0b00001011,
  Letter_S = 0b10110111,
  Letter_T = 0b00011111,
  Letter_U = 0b01111101,
  Letter_V = 0b01111101,
  Letter_W = 0b01010111,
  Letter_X = 0b01101111,
  Letter_Y = 0b01110111,
  Letter_Z = 0b01100001,
  _Space = 0b00000001,
};

enum Cyrillic {
  CyLetter_cA = Letters::Letter_A,
  CyLetter_cB = Digits::_6,
  CyLetter_cV = 0b11111111,
  CyLetter_cG = 0b10001101,
  CyLetter_cD = Letters::Letter_D,
  CyLetter_cYe = Letters::Letter_E,
  CyLetter_cZ = Digits::_3,
  CyLetter_cI = 0b01101101,
  CyLetter_cK = Letters::Letter_K,
  CyLetter_cL = Letters::Letter_N,
  CyLetter_cM = Letters::Letter_M,
  CyLetter_cN = Letters::Letter_H,
  CyLetter_cO = Letters::Letter_O,
  CyLetter_cP = Letters::Letter_N,
  CyLetter_cR = Letters::Letter_P,
  CyLetter_cS = Letters::Letter_C,
  CyLetter_cT = Letters::Letter_T,
  CyLetter_cU = 0b01110111,
  CyLetter_cH = Letters::Letter_X,
  CyLetter_cTs = Letters::Letter_U,
  CyLetter_cCh = Digits::_4,
  CyLetter_cE = Digits::_3,
  CyLetter_cYa = 0b11101111,

  CyLetter_c0 = 0b11111111,
  CyLetter_cY = Letters::Letter_Y,
};

enum Special {
  _Minus = 0b00000011,
};

#endif