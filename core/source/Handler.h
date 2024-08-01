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
  void drawBoard();
  void renderWhite(int last, int k, int i);
  void renderBlack(int last, int k, int i);
  const int SCREEN_WIDTH = 1000;
  const int SCREEN_HEIGHT = 1000;
  const int CHESS_TAB_WIDTH = 8;
  const int CHESS_TAB_HEIGHT = 8;
public:
  Handler();
  ~Handler();
  void GameLoop();
};
