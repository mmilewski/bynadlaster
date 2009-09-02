#include "Text.h"
#include "Renderer.h"


void Text::PrintString(Position position, std::string text) {
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
      Renderer::Get().DrawSprite(Position(position.x + i, position.y),
				 tc, Size(0.025, 0.025));
    }
  }
}
