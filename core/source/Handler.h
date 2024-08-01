#pragma once
#include <SDL_surface.h>
#include <SDL_video.h>

class Handler {
  SDL_Surface *m_background;
  SDL_Window *m_window;
  static bool isRunning;

private:
  bool init();
  void close();

public:
  Handler();
  static void GameLoop();
};
