#include "Text.h"
#include "Renderer.h"
#include <boost/lexical_cast.hpp>



void Text::PrintString(Position position, std::string text, Color color, Size size) {
  std::transform(text.begin(), text.end(), text.begin(), tolower);

  for (size_t i = 0; i < text.length(); ++i) {
    TexCoords tc(755, 911, 8, 7);
    char ch = text.at(i);

    if (ch >= 'a' && ch < 't') {
      tc.left = 755 + (text.at(i) - 'a') * 8;
    }
    else if (ch >= 't' && ch <= 'z') {
      tc.left = 755 + (text.at(i) - 'a') * 8 - 1; // shift on T
    }
    else if (ch == '!') {
      tc.left = 755;
      tc.bottom = 919;
    }
    else if (ch == '.') {
      tc.left = 755 + 8;
      tc.bottom = 919;
    }
    else if (ch == '<') {
      tc.left = 755 + 16;
      tc.bottom = 919;      
    }
    else if (ch == '>') {
      tc.left = 755 + 40;
      tc.bottom = 919;
    }
    else if (ch >= '0' && ch <= '9') {
      tc.left = 755 + 48 + (ch - '0') * 8;
      tc.bottom = 919;
    }

    if (ch != ' ') { // for 'space' we don't have to draw anything
      Renderer::Get().DrawSpriteAbsolute(Position(position.x + i * size.width, position.y), tc, color, size);
    }
  }
}


void Text::PrintString(Position position, std::string text, Color color) {
  PrintString(position, text, color, Size(0.02, 0.03));
}


void Text::PrintString(Position position, std::string text) {
  PrintString(position, text, Color(1,1,1));
}


void Text::PrintNumber(Position position, int number) {
  PrintNumber(position, number, Color(1,1,1));
}


void Text::PrintNumber(Position position, int number, Color color) {
  PrintNumber(position, number, color, Size(0.02, 0.03));
}


void Text::PrintNumber(Position position, int number, Color color, Size size) {
  std::string text = boost::lexical_cast<std::string>(number);
  PrintString(position, text, color, size);
}


void Text::PrintStage(Position position, size_t level, size_t stage, Size size) {
  Renderer::Get().DrawSpriteAbsolute(position, TexCoords(224, 77, 100, 13), size);

  PrintStageDigit(Position(position.x + 6 * size.width / 10.0, position.y), 
		  level,
		  Size(size.width/10, size.height));

  PrintStageDigit(Position(position.x + 8.5 * size.width / 10.0, position.y), 
		  stage,
		  Size(size.width/10, size.height));
}


void Text::PrintStageCenter(size_t level, size_t stage) {
  PrintStage(Position(0.5 - 0.25/2.0, 0.5 - 0.1/2.0), level, stage, Size(0.25, 0.1));
}


void Text::PrintStageDigit(Position position, size_t digit, Size size) {
  TexCoords tc(201 + digit * 8, 108, 8, 13);
  Renderer::Get().DrawSpriteAbsolute(position, tc, size);
}


void Text::PrintRound(Position position, int round_num, Size size) {
  TexCoords tc(76, 943, 49, 14);
  Renderer::Get().DrawSpriteAbsolute(position, tc, size);
  PrintRoundDigit(Position(position.x + size.width * 5.5 / 5.0, position.y), 
		  round_num, 
		  Size(size.width / 5, size.height));
}


void Text::PrintRound(Position position, int round_num) {
  PrintRound(position, round_num, Size(0.2, 0.06));
}


void Text::PrintRoundCenter(int round_num) {
  PrintRound(Position(0.5 - 0.2/2.0, 0.5 - 0.06/2.0), round_num, Size(0.2, 0.06));
}


void Text::PrintRoundDigit(Position position, int digit, Size size) {
  TexCoords tc(137, 942, 91 / 9 + digit * size.width, 14);
  Renderer::Get().DrawSpriteAbsolute(position, tc, size);
}
