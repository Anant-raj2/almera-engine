#include "Handler.h"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include <GL/gl.h>
#include <SDL_opengl.h>
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
    std::cout << "Could Not init the video system: " << SDL_GetError() << '\n';
    success = false;
    return success;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  window = SDL_CreateWindow(
      "Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
      SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << '\n';
    success = false;
    return success;
  }

  glContext = SDL_GL_CreateContext(window);
  if (glContext == nullptr) {
    std::cout << "Could not create Opengl Context: " << SDL_GetError() << '\n';
    success = false;
    return success;
  }
  if (SDL_GL_SetSwapInterval(1) < 0) {
    std::cout << "Failed to Set VSync! " << SDL_GetError() << '\n';
  }

  if (!initGL()) {
    std::cout << "Failed to initialize Opengl: " << SDL_GetError() << '\n';
    success = false;
    return success;
  }

  return success;
}
