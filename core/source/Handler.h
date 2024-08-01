#pragma once
#include "SDL_render.h"
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstdlib>

class Handler {
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  bool isRunning;

private:
  bool init();
  void close();
  bool drawBoard();

public:
  Handler();
  ~Handler();
  void GameLoop();
};
