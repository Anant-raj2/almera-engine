#include <SDL_opengl.h>
#include <string>

class Logger {
private:
  Logger();
  ~Logger();
  enum LogLevels { INFO, WARNING, ERROR };
  LogLevels m_LogLevel = INFO;
  std::string getLogTime();

public:
  void LogError(std::string &msg, std::string &error);
  void LogWarning(std::string &msg);
  void LogInfo(std::string &msg);
  void SetLogLevel(LogLevels level);
  void PrintGLProgramLog(GLuint program);
  void PrintGLShaderLog(GLuint shader);
};
