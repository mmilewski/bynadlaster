#include "Renderer.h"

void Renderer::LoadTexture(std::string filename) {
  SDL_Surface* orgImage = IMG_Load(filename.c_str());
  if (!orgImage) {
    std::cerr << "Image loading failed " << filename << "\n";
    return;
  }
  int bpp = orgImage->format->BytesPerPixel;
  SDL_Surface* image = flip( orgImage, false, true, bpp==4?true:false);

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
  glTexCoord2f(texs.left,              texs.bottom);                glVertex2f(pos.x,             pos.y);
  glTexCoord2f(texs.left + texs.width, texs.bottom);                glVertex2f(pos.x + pos.width, pos.y);
  glTexCoord2f(texs.left + texs.width, texs.bottom + texs.height);  glVertex2f(pos.x + pos.width, pos.y + pos.height);
  glTexCoord2f(texs.left,              texs.bottom + texs.height);  glVertex2f(pos.x,             pos.y + pos.height);
  glEnd();
}


/* kod poniższej funkcji został ściągnięty z:
   http://michalis.ii.uni.wroc.pl/~michalis/teaching/pgk/c/sdl_utils.c
*/
SDL_Surface* Renderer::flip( SDL_Surface *in, bool x, bool y, bool rgba )
{
    /* masks for various endianesses added by Michalis.
       SDL_CreateRGBSurface docs example
       [http://www.libsdl.org/cgi/docwiki.cgi/SDL_5fCreateRGBSurface]
       suggests that there is no nicer way to do this portably ? */
    Uint32 rgba_rmask;
    Uint32 rgba_gmask;
    Uint32 rgba_bmask;
    Uint32 rgba_amask;

    Uint32 rgb_rmask;
    Uint32 rgb_gmask;
    Uint32 rgb_bmask;

    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        rgba_rmask = 0xff000000;
        rgba_gmask = 0x00ff0000;
        rgba_bmask = 0x0000ff00;
        rgba_amask = 0x000000ff;

        rgb_rmask = 0xff0000;
        rgb_gmask = 0x00ff00;
        rgb_bmask = 0x0000ff;
    } else
    {
        rgba_rmask = 0x000000ff;
        rgba_gmask = 0x0000ff00;
        rgba_bmask = 0x00ff0000;
        rgba_amask = 0xff000000;

        rgb_rmask = 0x0000ff;
        rgb_gmask = 0x00ff00;
        rgb_bmask = 0xff0000;
    }

    SDL_Surface *out, *tmp;
    SDL_Rect from_rect, to_rect;
    Uint32      flags;
    Uint32  colorkey=0;

    /* --- grab the settings for the incoming pixmap --- */

    SDL_LockSurface(in);
    flags = in->flags;

    /* --- change in's flags so ignore colorkey & alpha --- */

    if (flags & SDL_SRCCOLORKEY) {
        in->flags &= ~SDL_SRCCOLORKEY;
        colorkey = in->format->colorkey;
    }
    if (flags & SDL_SRCALPHA) {
        in->flags &= ~SDL_SRCALPHA;
    }

    SDL_UnlockSurface(in);

    /* --- create our new surface --- */

    if (rgba) {
        out = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            in->w, in->h, 32, rgba_rmask, rgba_gmask, rgba_bmask, rgba_amask);
    } else
    {
        out = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            in->w, in->h, 24, rgb_rmask, rgb_gmask, rgb_bmask, 0);
    }

    /* --- flip horizontally if requested --- */

    if (x) {
        from_rect.h = to_rect.h = in->h;
        from_rect.w = to_rect.w = 1;
        from_rect.y = to_rect.y = 0;
        from_rect.x = 0;
        to_rect.x = in->w - 1;

        do {
            SDL_BlitSurface(in, &from_rect, out, &to_rect);
            from_rect.x++;
            to_rect.x--;
        } while (to_rect.x >= 0);
    }

    /* --- flip vertically if requested --- */

    if (y) {
        from_rect.h = to_rect.h = 1;
        from_rect.w = to_rect.w = in->w;
        from_rect.x = to_rect.x = 0;
        from_rect.y = 0;
        to_rect.y = in->h - 1;

        do {
            SDL_BlitSurface(in, &from_rect, out, &to_rect);
            from_rect.y++;
            to_rect.y--;
        } while (to_rect.y >= 0);
    }

    /* --- restore colorkey & alpha on in and setup out the same --- */

    SDL_LockSurface(in);

    if (flags & SDL_SRCCOLORKEY) {
        in->flags |= SDL_SRCCOLORKEY;
        in->format->colorkey = colorkey;
        tmp = SDL_DisplayFormat(out);
        SDL_FreeSurface(out);
        out = tmp;
        out->flags |= SDL_SRCCOLORKEY;
        out->format->colorkey = colorkey;
    } else if (flags & SDL_SRCALPHA) {
        in->flags |= SDL_SRCALPHA;
        tmp = SDL_DisplayFormatAlpha(out);
        SDL_FreeSurface(out);
        out = tmp;
    } else {
        tmp = SDL_DisplayFormat(out);
        SDL_FreeSurface(out);
        out = tmp;
    }

    SDL_UnlockSurface(in);

    /* Michalis says:
       Ouh. Looks like CreateRGBSurface doesn't try too hard to satisfy
       it's parameters bitsPerPixel, Rmask, Gmask, Bmask, Amask.

       1. For RGB case, it's confirmed that the resulting image may
       have 4 bytes per pixel, even though we wanted 24 bits per pixel.
       But we don't want this, we want to use OpenGL's GL_RGB
       format with this image's data.

       2. For RGBA case, we can get surface with format
       R/G/B/A mask: FF0000 FF00 FF FF000000
       which is completely different than what we requested with
       rgba_xxx parameters. This can be seen with sdl_image_draw_alpha.c
       that prints image format.

       It seems that the only way to be sure about the format is to use
       SDL_ConvertSurface --- this tries really hard to give us the
       requested format. */
    {
        SDL_PixelFormat format;
        format.palette = NULL;
        if (rgba) {
            format.BitsPerPixel = 32;
            format.BytesPerPixel = 4;
        } else {
            format.BitsPerPixel = 24;
            format.BytesPerPixel = 3;
        }
        format.Rloss = 0;
        format.Gloss = 0;
        format.Bloss = 0;
        format.Aloss = 0;
        format.Rshift = 0;
        format.Gshift = 0;
        format.Bshift = 0;
        format.Ashift = 0;
        if (rgba)
        {
            format.Rmask = rgba_rmask;
            format.Gmask = rgba_gmask;
            format.Bmask = rgba_bmask;
            format.Amask = rgba_amask;
        } else {
            format.Rmask = rgb_rmask;
            format.Gmask = rgb_gmask;
            format.Bmask = rgb_bmask;
            format.Amask = 0;
        }
        format.colorkey = 0;
        format.alpha = 0;
        SDL_Surface* tmp = SDL_ConvertSurface(out, &format, SDL_SWSURFACE);
        SDL_FreeSurface(out);
        out = tmp;
    }
    return out;
}
