#include "Handler.h"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_video.h"
#include <GL/gl.h>
#include <GL/glu.h>
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
    std::cout << "Failed to initialize Opengl: " << '\n';
    success = false;
    return success;
  }

  return success;
}

bool Handler::initGL() {
  bool success = true;
  GLenum error = GL_NO_ERROR;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cout << "Failed to initialize Opengl: " << gluErrorString(error);
    success = false;
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cout << "Failed to initialize Opengl: " << gluErrorString(error);
    success = false;
  }

  glClearColor(0.f, 0.f, 0.f, 1.f);
  error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cout << "Failed to initialize Opengl: " << gluErrorString(error);
    success = false;
  }

  return success;
}

void Handler::handleKeys(unsigned char key, int x, int y) {
  if (key == 'q') {
    renderQuad = !renderQuad;
  }
}

void Handler::update() {}

void Handler::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  if (renderQuad) {
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
  }
}

void Handler::GameLoop() {
  SDL_StartTextInput();

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      } else if (e.type == SDL_TEXTINPUT) {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        handleKeys(e.text.text[0], x, y);
      }
    }
    render();
    SDL_GL_SwapWindow(window);
  }
  SDL_StopTextInput();
  close();
}

void Handler::close() {
  SDL_DestroyWindow(window);
  window = nullptr;
  SDL_Quit();
}
