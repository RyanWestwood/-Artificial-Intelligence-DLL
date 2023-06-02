#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct RenderData
{
  SDL_Window*   windows  = nullptr;
  SDL_Renderer* renderer = nullptr;
};

RenderData InitializeRenderer(int width, int height)
{
  SDL_Window*   window   = nullptr;
  SDL_Renderer* renderer = nullptr;
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << "\n";
    return {};
  }
  else
  {
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
      std::cout << "Warning: Linear texture filtering not enabled!"
                << "\n";
    }
    window = SDL_CreateWindow("AIL Sandbox",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
      std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
      return {};
    }
    else
    {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if(renderer == NULL)
      {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError()
                  << "\n";
        return {};
      }
      else
      {
        SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags))
        {
          std::cout << "SDL_image could not be initialized! SDL_image error: "
                    << IMG_GetError() << "\n";
          return {};
        }
      }
    }
  }
#ifdef LOGGING
  std::cout << "Renderer Initialized!\n";
#endif // LOGGING
  return RenderData{window, renderer};
}

struct TextureData
{
  SDL_Texture* m_Texture;
  SDL_Rect     m_Source;
};

TextureData LoadSolidColourTexture(SDL_Colour colour, SDL_Point dimensions, SDL_Renderer* renderer)
{
  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif
#ifdef LOGGING
  std::cout << "Loading debug texture: "
            << "\n";
#endif // LOGGING`
  try
  {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(surface,
                 NULL,
                 SDL_MapRGBA(surface->format, colour.r, colour.g, colour.b, colour.a));
    if(surface == nullptr)
      throw;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == nullptr)
      throw;
    SDL_Rect source = {0, 0, surface->w, surface->h};
    SDL_FreeSurface(surface);
    return {texture, source};
  }
  catch(std::exception& e)
  {
    std::cout << "An exception was thrown."
              << "\n";
    std::cout << "\t" << e.what() << "\t" << IMG_GetError() << "\n";
    return {};
  }
}
