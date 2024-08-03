#pragma once
#include "SDL_video.h"
#include <SDL.h>
#include <SDL_opengl.h>

class Handler {

public:
  SDL_Window *window;
  SDL_GLContext glContext;
  bool renderQuad = true;
  bool isRunning = true;
  GLuint programID = 0;
  GLint vertexPos2DLocation = -1;
  GLuint VBO = 0;
  GLuint IBO = 0;

private:
  const int SCREEN_WIDTH = 600;
  const int SCREEN_HEIGHT = 600;
  const int CHESS_TAB_WIDTH = 8;
  const int CHESS_TAB_HEIGHT = 8;
  const int PIECE_WIDTH = SCREEN_WIDTH / 8;
  const int PIECE_HEIGHT = SCREEN_HEIGHT / 8;
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
  void printGLProgramLog(GLuint program);
  void printGLShaderLog(GLuint shader);
};
