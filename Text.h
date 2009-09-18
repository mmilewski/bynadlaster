#ifndef __TEXT_H_INCLUDED__
#define __TEXT_H_INCLUDED__

#include "StdAfx.h"

class Text {
public:
  void PrintString(std::string text, Position position, Color color, Size size);
  void PrintString(std::string text, Position position, Color color);
  void PrintString(std::string text, Position position);
  void DrawGlyph(char glyph, Position position, Color color, Size size);

  void PrintNumber(int number, Position position, Color color, Size size);
  void PrintNumber(int number, Position position, Color color);
  void PrintNumber(int number, Position position);
  
  void PrintStage(size_t level, size_t stage, Position position, Size size);
  void PrintStageCenter(size_t level, size_t stage);

  void PrintRound(int round_num, Position position, Size size);
  void PrintRound(int round_num, Position position);
  void PrintRoundCenter(int round_num);

protected:
  void PrintStageDigit(size_t digit, Position position, Size size);
  void PrintRoundDigit(int digit, Position position, Size size);

};


#endif
