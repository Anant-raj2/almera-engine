#include "Handler.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <SDL.h>
#include <iostream>

bool Handler::isRunning = true;

Handler::Handler() {
  if (!init()) {
    std::cout << "Cannot initialize SDL2 Handler: " << SDL_GetError() << '\n';
  }
}

bool Handler::init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
    return success;
  } else {
    SDL_Window *gWindow =
        SDL_CreateWindow("Event Window", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
    if (!gWindow) {
      success = false;
      return success;
    } else {
      SDL_Surface *gBackground = SDL_GetWindowSurface(gWindow);
      SDL_FillRect(gBackground, nullptr,
                   SDL_MapRGB(gBackground->format, 235, 64, 52));
    }
  }
  return success;
}

void Handler::GameLoop() {
  while (isRunning) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
    }
  }
}
