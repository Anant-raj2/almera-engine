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
  for (int k{}; k < CHESS_TAB_HEIGHT; k++) {
    for (int i{}; i < CHESS_TAB_WIDTH; i++) {
      if (k % 2 == 0) {
        if (i % 2 == 0) {
          SDL_Rect fillRect = {i * 125, k * 125, 125, 125};
          SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
          SDL_RenderFillRect(m_renderer, &fillRect);
        } else {
          SDL_Rect fillRect = {i * 125, k * 125, 125, 125};
          SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
          SDL_RenderFillRect(m_renderer, &fillRect);
        }
      } else {
        if (i % 2 == 0) {
          SDL_Rect fillRect = {i * 125, k * 125, 125, 125};
          SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
          SDL_RenderFillRect(m_renderer, &fillRect);
        } else {
          SDL_Rect fillRect = {i * 125, k * 125, 125, 125};
          SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
          SDL_RenderFillRect(m_renderer, &fillRect);
        }
      }
    }
  }
  // int counter = 0;
  // for (int i{}; i < CHESS_TAB_WIDTH; i++) {
  //   for (int k{}; k < CHESS_TAB_HEIGHT; k++) {
  //     if (counter % 2 == 0) {
  //       SDL_Rect fillRect = {i * 125, k * 125, 125, 125};
  //       SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
  //       SDL_RenderFillRect(m_renderer, &fillRect);
  //     } else {
  //       SDL_Rect fillRect = {i * 125, k * 125, 125, 125};
  //       SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
  //       SDL_RenderFillRect(m_renderer, &fillRect);
  //     }
  //     counter++;
  //   }
  // }
  // bool white = true;
  // SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  //
  // for (int i = 0; i < 8; i++)
  // {
  // 	for (int j = 0; j < 8; j++)
  // 	{
  // 		if (white)
  // 		{
  // 			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  // 		}
  // 		else
  // 		{
  // 			SDL_SetRenderDrawColor(m_renderer, 155, 103, 60, 255);
  // 		}
  // 		white = !white;
  // 		SDL_Rect rectangle = { i * SCREEN_WIDTH / 8,
  // 							  j * SCREEN_HEIGHT / 8,
  // 							  SCREEN_WIDTH / 8,
  // 							  SCREEN_HEIGHT / 8 };
  // 		SDL_RenderFillRect(m_renderer, &rectangle);
  // 	}
  // 	white = !white;
  // }
  // for (int i = 0; i < 8; i++) {
  //   for (int k = 0; k < 8; k++) {
  //     if (board[i][k] == 0) {
  //       SDL_Rect fillRect = {k * 125, i * 125, 125, 125};
  //       SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
  //       SDL_RenderFillRect(m_renderer, &fillRect);
  //     } else {
  //       SDL_Rect fillRect = {k * 125, i * 125, 125, 125};
  //       SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
  //       SDL_RenderFillRect(m_renderer, &fillRect);
  //     }
  //   }
  // }
  // int startPos = 0;
  // for (int y = 0; y < 8; y++) {
  //   for (int x = startPos; x < 3; x += 2) {
  //     SDL_Rect rect;
  //     rect.x = x * SCREEN_WIDTH/8;
  //     rect.y = y * SCREEN_HEIGHT/8;
  //     rect.w = 125;
  //     rect.h = 125;
  //     SDL_SetRenderDrawColor(m_renderer, 159, 84, 8, 255);
  //     SDL_RenderFillRect(m_renderer, &rect);
  //   }
  //   startPos = 1 - startPos;
  // }
  // SDL_Rect Box = {0, 0, 80, 80};
  // bool toggle_color = 0;
  // for (int i = 0; i < 8; i++) {
  //   for (int j = 0; j < 8; j++) {
  //     if (toggle_color)
  //       SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  //     else
  //       SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  //     SDL_RenderFillRect(m_renderer, &Box);
  //     Box.x += 80;
  //     if (j != 7) // needed for chess color pattern
  //       toggle_color = !toggle_color;
  //   }
  //   Box.x = 0;
  //   Box.y += 80;
  // }
  // for (int k{}; k < CHESS_TAB_HEIGHT; k++) {
  //   for (int i{8}; i >= 0; i--) {
  //     // SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
  //     SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
  //     SDL_Rect box = {(i-k) * SCREEN_WIDTH / 8, (i-k) * SCREEN_HEIGHT / 8,
  //                     SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8};
  //     SDL_RenderFillRect(m_renderer, &box);
  //   }
  // }
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
