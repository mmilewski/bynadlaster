#include "Renderer.h"

void Renderer::LoadTexture(std::string filename) {
  SDL_Surface* image = IMG_Load(filename.c_str());

  if (!image) {
    std::cerr << "Image loading failed " << filename << "\n";
    return;
  }

  GLuint textures[1];
  glGenTextures(1, textures);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
      
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  if (image->format->Amask) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 
		 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
  }
  else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 
		 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  }

  SDL_FreeSurface(image);
}

void Renderer::DrawSprite(Position pos, TexCoords texs) {
  glBegin(GL_QUADS);
  glTexCoord2f(texs.left, texs.bottom); glVertex2f(pos.x, pos.y);
  glTexCoord2f(texs.right, texs.bottom); glVertex2f(pos.x + pos.width, pos.y);
  glTexCoord2f(texs.right, texs.top); glVertex2f(pos.x + pos.width, pos.y + pos.height);
  glTexCoord2f(texs.left, texs.top); glVertex2f(pos.x, pos.y + pos.height);
  glEnd();
}

