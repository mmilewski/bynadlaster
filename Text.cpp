#include "Engine.h"
#include "Text.h"
#include <boost/lexical_cast.hpp>



void Text::PrintString(std::string text, Position position, Color color, Size size) {
  std::transform(text.begin(), text.end(), text.begin(), tolower);

  for (size_t i = 0; i < text.length(); ++i) {
    DrawGlyph(text.at(i), Position(position.x + i * size.width, position.y), color, size);
  }
}


void Text::DrawGlyph(char glyph, Position position, Color color, Size size) {
    TexCoords tc(755, 911, 8, 7);
    char ch = glyph;

    if (ch >= 'a' && ch < 't') {
      tc.left = 755 + (ch - 'a') * 8;
    }
    else if (ch >= 't' && ch <= 'z') {
      tc.left = 755 + (ch - 'a') * 8 - 1; // shift on T
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
      Engine::Get().Renderer()->DrawSpriteAbsolute(tc, position, color, size);
    }
}


void Text::PrintString(std::string text, Position position, Color color) {
  PrintString(text, position, color, Size(0.02, 0.03));
}


void Text::PrintString(std::string text, Position position) {
  PrintString(text, position, Color(1,1,1));
}


void Text::PrintNumber(int number, Position position) {
  PrintNumber(number, position, Color(1,1,1));
}


void Text::PrintNumber(int number, Position position, Color color) {
  PrintNumber(number, position, color, Size(0.02, 0.03));
}


void Text::PrintNumber(int number, Position position, Color color, Size size) {
  std::string text = boost::lexical_cast<std::string>(number);
  PrintString(text, position, color, size);
}


void Text::PrintStage(size_t level, size_t stage, Position position, Size size) {
  Engine::Get().Renderer()->DrawSpriteAbsolute(TexCoords(224, 77, 100, 13), position, size);

  PrintStageDigit(level,
		  Position(position.x + 6 * size.width / 10.0, position.y), 
		  Size(size.width/10, size.height));

  PrintStageDigit(stage,
		  Position(position.x + 8.5 * size.width / 10.0, position.y), 
		  Size(size.width/10, size.height));
}


void Text::PrintStageCenter(size_t level, size_t stage) {
  PrintStage(level, stage, Position(0.5 - 0.25/2.0, 0.5 - 0.1/2.0), Size(0.25, 0.1));
}


void Text::PrintStageDigit(size_t digit, Position position, Size size) {
  TexCoords tc(201 + digit * 8, 108, 8, 13);
  Engine::Get().Renderer()->DrawSpriteAbsolute(tc, position, size);
}


void Text::PrintRound(int round_num, Position position, Size size) {
  TexCoords tc(76, 943, 49, 14);
  Engine::Get().Renderer()->DrawSpriteAbsolute(tc, position, size);
  PrintRoundDigit(round_num,
		  Position(position.x + size.width * 5.5 / 5.0, position.y), 
		  Size(size.width / 5, size.height));
}


void Text::PrintRound(int round_num, Position position) {
  PrintRound(round_num, position, Size(0.2, 0.06));
}


void Text::PrintRoundCenter(int round_num) {
  PrintRound(round_num, Position(0.5 - 0.2/2.0, 0.5 - 0.06/2.0), Size(0.2, 0.06));
}


void Text::PrintRoundDigit(int digit, Position position, Size size) {
  TexCoords tc(137, 942, 91 / 9 + digit * size.width, 14);
  Engine::Get().Renderer()->DrawSpriteAbsolute(tc, position, size);
}
