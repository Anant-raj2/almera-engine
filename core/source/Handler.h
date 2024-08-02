#pragma once
#include "SDL_video.h"
#include <SDL.h>

class Handler {

public:
  SDL_Window *window;
  SDL_GLContext glContext;
  bool renderQuad = true;

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

private:
  bool init();
  bool initGL();
  void handleKeys(unsigned char key, int x, int y);
  void update();
  void render();
  void close();
};
