#include "Renderer.h"
#include "Text.h"
#include "Menu.h"


Menu::Menu() 
  : m_camera_y(0.75),
    m_current_option(Menu::START_GAME) {
}


void Menu::DoDraw() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0, -m_camera_y, 0);

  Renderer::Get().DrawQuad(Position(0,0.75), Color(0.325, 0.451, 0.827), Size(1,1)); // why does this colour looks as wrong one?
  Renderer::Get().DrawSpriteAbsolute(Position(0,0), TexCoords(643,869,256,146), Size(1,0.75));
  Renderer::Get().DrawSpriteAbsolute(Position(0.25,0.70), TexCoords(653,919,89,50), Size(0.349/2,0.255/2));
  Renderer::Get().DrawSpriteAbsolute(Position(0.25+0.349/2,0.7+0.082/2), TexCoords(742,903,175,34), Size(0.686/2,0.173/2));

  Text text;
  text.PrintString(Position(0.35, 0.43), "push fire button", Color(1,1,0));
  text.PrintString(Position(0.4, 0.3), "game start");
  text.PrintString(Position(0.4, 0.25), "quit");

  // show marker
  double x = 0.35;
  double y = 0.3;
  switch (m_current_option) {
  case Menu::START_GAME:
    y = 0.3;
    break;

  case Menu::QUIT_GAME:
    y = 0.25;
    break;

  default:
    break;
  }
  Renderer::Get().DrawSpriteAbsolute(Position(x,y), TexCoords(747,912,8,8), Size(0.031, 0.031));
  
  SDL_GL_SwapBuffers();
}


void Menu::DoUpdate(double dt) {
  if (m_camera_y <= 0.0) {
    m_camera_y = 0.0;
    return;
  }
  else {
    m_camera_y -= 0.3 * dt;
  }
}


bool Menu::DoHandleInput(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_DOWN) {
      m_current_option = Menu::Option((m_current_option + Menu::OPTIONS_COUNT - 1) % Menu::OPTIONS_COUNT);
      return true;
    }
    else if (event.key.keysym.sym == SDLK_UP) {
      m_current_option = Menu::Option((m_current_option + 1) % Menu::OPTIONS_COUNT);
      return true;
    }
    else if (event.key.keysym.sym == SDLK_RETURN) {
      Finish();
      return true;
    }
  }

  return false;
}
