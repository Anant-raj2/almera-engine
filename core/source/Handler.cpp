#include "Handler.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_rect.h"
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
    if (IMG_Init(IMG_INIT_PNG) == 0) {
      success = false;
      return success;
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

SDL_Texture* SDL_Handler::loadImage(std::string filename)
{
	SDL_Surface* loadedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage == NULL)
	{
		std::cout << "couldnt load " << filename << std::endl;
	}

	SDL_Texture* text = SDL_CreateTextureFromSurface(m_renderer, loadedImage);

	return text;
}

void SDL_Handler::renderBackground()
{
	bool white = true;
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (white)
			{
				SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
			}
			else
			{
				SDL_SetRenderDrawColor(m_renderer, 155, 103, 60, 255);
			}
			white = !white;
			SDL_Rect rectangle = { i * SCREEN_WIDTH / 8,
								  j * SCREEN_HEIGHT / 8,
								  SCREEN_WIDTH / 8,
								  SCREEN_HEIGHT / 8 };
			SDL_RenderFillRect(m_renderer, &rectangle);
		}
		white = !white;
	}
}

void SDL_Handler::undoPieceRender(int x, int y)
{
	if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer, 155, 103, 60, 255);
	}
	SDL_Rect rectangle = { x * SCREEN_WIDTH / 8,
						  y * SCREEN_HEIGHT / 8,
						  SCREEN_WIDTH / 8,
						  SCREEN_HEIGHT / 8 };
	SDL_RenderFillRect(m_renderer, &rectangle);
}

void SDL_Handler::cleanUp()
{
	SDL_FreeSurface(m_screenSurface);
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}


void Handler::drawBoard() {
  SDL_Rect fillRect;
  for (int k{}; k < CHESS_TAB_HEIGHT; k++) {
    for (int i{}; i < CHESS_TAB_WIDTH; i++) {
      if (k % 2 == 0) {
        i % 2 ? SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255)
              : SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
      } else {
        i % 2 ? SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255)
              : SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);
      }
      fillRect = {i * SCREEN_WIDTH / CHESS_TAB_HEIGHT,
                  k * SCREEN_HEIGHT / CHESS_TAB_HEIGHT, PIECE_WIDTH,
                  PIECE_HEIGHT};
      SDL_RenderFillRect(m_renderer, &fillRect);
    }
  }
}

SDL_Texture *Handler::loadTexture(const char *path) {
  SDL_Texture *texture = IMG_LoadTexture(m_renderer, path);
  if (!texture) {
    std::cout << "Could not load texture" << SDL_GetError() << '\n';
  }
  return texture;
}

void Handler::GameLoop() {
  SDL_Texture *texture =
      loadTexture("../assets/pieces/png/extra/Chess_bdt60.png");
  SDL_Rect chessRect = {SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8, PIECE_WIDTH,
                        PIECE_HEIGHT};
  drawBoard();
  while (isRunning) {
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
      if (event.type == SDL_QUIT) {
        // Break out of the loop on quit
        isRunning = false;
        break;
      }
    }
    SDL_RenderCopy(m_renderer, texture, NULL, &chessRect);
    SDL_RenderPresent(m_renderer);
  }
  SDL_DestroyTexture(texture);
  IMG_Quit();
  close();
}
