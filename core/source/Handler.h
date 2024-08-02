#pragma once
#include "SDL_render.h"
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstdlib>
#include "SDL_render.h"
#include "SDL_video.h"
#include <SDL.h>
#include <SDL_image.h>

class Handler {

public:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  bool isRunning;

private:
  const int SCREEN_WIDTH = 600;
  const int SCREEN_HEIGHT = 600;
  const int CHESS_TAB_WIDTH = 8;
  const int CHESS_TAB_HEIGHT = 8;
  const int PIECE_WIDTH = SCREEN_WIDTH/8;
  const int PIECE_HEIGHT = SCREEN_HEIGHT/8;

public:
  Handler();
  ~Handler();
  void GameLoop();

private:
  bool init();
  void close();
  void drawBoard();
  SDL_Texture* loadTexture(const char* path);
};
