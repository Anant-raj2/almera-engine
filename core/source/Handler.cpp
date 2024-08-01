#include "Handler.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <SDL.h>
#include <iostream>

Handler::Handler() {
  if (!init()) {
    std::cout << "Cannot initialize SDL2 Handler: " << SDL_GetError() << '\n';
  }
}

Handler::~Handler() { close(); }

bool Handler::init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
    return success;
  } else {
    m_window =
        SDL_CreateWindow("Event Window", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
    if (!m_window) {
      success = false;
      return success;
    } else {
      m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
      if (!m_renderer) {
        std::cout << "Error creating renderer: " << SDL_GetError() << '\n';
      }
    }
  }
  return success;
}

void Handler::close() {
  SDL_DestroyWindow(m_window);
  m_window = nullptr;
  SDL_DestroyRenderer(m_renderer);
  m_renderer = nullptr;
  SDL_Quit();
}

bool Handler::drawBoard() {
  return true;
}
void Handler::GameLoop() {
  Uint8 red;
  Uint8 green;
  Uint8 blue;
  while (isRunning) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        // Break out of the loop on quit
        isRunning = false;
        break;
      }
    }
    // Randomly change the colour
    red = rand() % 255;
    green = rand() % 255;
    blue = rand() % 255;
    // Fill the screen with the colour
    SDL_SetRenderDrawColor(m_renderer, red, green, blue, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
  }
}
