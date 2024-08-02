#pragma once
#include "SDL_video.h"
#include <SDL.h>

class Handler {

public:
  SDL_Window *window;
  SDL_GLContext glContext;
  bool renderQuad = true;
  bool isRunning = true;

private:
  const int SCREEN_WIDTH = 600;
  const int SCREEN_HEIGHT = 600;
  const int CHESS_TAB_WIDTH = 8;
  const int CHESS_TAB_HEIGHT = 8;
  const int PIECE_WIDTH = SCREEN_WIDTH/8;
  const int PIECE_HEIGHT = SCREEN_HEIGHT/8;
  SDL_Event e;

public:
  Handler();
  ~Handler();
  void GameLoop();

private:
  bool init();
  bool initGL();
  void handleKeys(unsigned char key, int x, int y);
  void update();
  void render();
  void close();
};
