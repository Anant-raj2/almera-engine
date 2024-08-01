#include "Handler.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_rect.h"
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
    m_window = SDL_CreateWindow("Event Window", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void Handler::renderWhite(int last, int k, int i) {
  SDL_Rect fillRect = {k * 125, i * 125, 125, 125};
  SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
  SDL_RenderFillRect(m_renderer, &fillRect);
}

void Handler::renderBlack(int last, int k, int i) {
  SDL_Rect fillRect = {k * 125, i * 125, 125, 125};
  SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
  SDL_RenderFillRect(m_renderer, &fillRect);
}

void Handler::drawBoard() {
  SDL_Rect fillRect;
  for (int k{}; k < CHESS_TAB_HEIGHT; k++) {
    for (int i{}; i < CHESS_TAB_WIDTH; i++) {
      if (k % 2 == 0) {
        if (i % 2 == 0) {
          SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
        } else {
          SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
        }
      } else {
        if (i % 2 == 0) {
          SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
        } else {
          SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
        }
      }
      fillRect = {i * 125, k * 125, 125, 125};
      SDL_RenderFillRect(m_renderer, &fillRect);
    }
  }
}

void Handler::GameLoop() {
  while (isRunning) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        // Break out of the loop on quit
        isRunning = false;
        break;
      }
    }
    drawBoard();
    SDL_RenderPresent(m_renderer);
  }
}
