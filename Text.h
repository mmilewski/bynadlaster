#ifndef __TEXT_H_INCLUDED__
#define __TEXT_H_INCLUDED__

#include "StdAfx.h"

class Text {
public:
  void PrintString(Position position, std::string text, Size size);
  void PrintString(Position position, std::string text);
  void PrintNumber(Position position, int number, Size size);
  void PrintNumber(Position position, int number);
  
  void PrintStage(Position position, size_t level, size_t stage, Size size);
  void PrintStageCenter(size_t level, size_t stage);

  void PrintRound(Position position, int round_num, Size size);
  void PrintRound(Position position, int round_num);
  void PrintRoundCenter(int round_num);
//   void PrintAfterKillPoints(Position position, AKP::AfterKillPoints points);
//   void PrintBynaDlaster(Position position);

//   void SetFontSizeInPx(Size size);

protected:
  void PrintStageDigit(Position position, size_t digit, Size size);
  void PrintRoundDigit(Position position, int digit, Size size);

private:
//   Size m_font_size;
};


#endif
