// clang-format off
#include <GL/glew.h>
#include "Handler.h"
#include "SDL_video.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <cstddef>
#include <iostream>
// clang-format on

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
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cout << "Error initializing GLEW!" << glewGetErrorString(glewError);
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

  programID = glCreateProgram();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  const GLchar *vertexShaderSource[] = {
      "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( "
      "LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"

  };

  glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

  glCompileShader(vertexShader);
  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
  if (vShaderCompiled != GL_TRUE) {
    std::cout << "Unable to compile vertexShader: " << vertexShader << '\n';
    success = false;
    printGLShaderLog(vertexShader);
  } else {
    glAttachShader(programID, vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragmentShaderSource[] = {
        "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( "
        "1.0, 1.0, 1.0, 1.0 ); }"};
    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
    if (fShaderCompiled != GL_TRUE) {
      std::cout << "Unable to compile fragment shader: " << fragmentShader
                << '\n';
      printGLShaderLog(fragmentShader);
      success = false;
    } else {
      glAttachShader(programID, fragmentShader);
      glLinkProgram(programID);

      GLint programSuccess = GL_TRUE;
      glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);
      if (programSuccess != GL_TRUE) {
        std::cout << "Error linking program " << programID << '\n';
        printGLProgramLog(programID);
        success = false;
      } else {
        vertexPos2DLocation = glGetAttribLocation(programID, "LVertexPos2D");
        if (vertexPos2DLocation == -1) {
          printf("LVertexPos2D is not a valid glsl program variable!\n");
          success = false;
        } else {
          // Initialize clear color
          glClearColor(0.f, 0.f, 0.f, 1.f);

          // VBO data
          GLfloat vertexData[] = {-0.5f, -0.5f, 0.5f,  -0.5f,
                                  0.5f,  0.5f,  -0.5f, 0.5f};

          // IBO data
          GLuint indexData[] = {0, 1, 2, 3};

          // Create VBO
          glGenBuffers(1, &VBO);
          glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData,
                       GL_STATIC_DRAW);

          // Create IBO
          glGenBuffers(1, &IBO);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData,
                       GL_STATIC_DRAW);
        }
      }
    }
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
  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Render quad
  if (renderQuad) {
    glUseProgram(programID);

    // Enable vertex position
    glEnableVertexAttribArray(vertexPos2DLocation);

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat), NULL);

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    // Disable vertex position
    glDisableVertexAttribArray(vertexPos2DLocation);

    // Unbind program
    glUseProgram(NULL);
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

void Handler::printGLProgramLog(GLuint program) {
  // Make sure name is shader
  if (glIsProgram(program)) {
    // Program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    // Get info string length
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // Allocate string
    char *infoLog = new char[maxLength];

    // Get info log
    glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
      // Print Log
      printf("%s\n", infoLog);
    }

    // Deallocate string
    delete[] infoLog;
  } else {
    printf("Name %d is not a program\n", program);
  }
}

void Handler::printGLShaderLog(GLuint shader) {
  // Make sure name is shader
  if (glIsShader(shader)) {
    // Shader log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    // Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    // Allocate string
    char *infoLog = new char[maxLength];

    // Get info log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
      // Print Log
      printf("%s\n", infoLog);
    }

    // Deallocate string
    delete[] infoLog;
  } else {
    printf("Name %d is not a shader\n", shader);
  }
}
