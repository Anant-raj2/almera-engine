#include <GL/glew.h>
#include "Logger.h"
#include <iostream>
#include <sstream>

void Logger::SetLogLevel(LogLevels level) { m_LogLevel = level; }

std::string Logger::getLogTime(){
  time_t now = time(0);
  tm *timeinfo = localtime(&now);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
  std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] " << std::endl;
  return logEntry.str();
}

void Logger::LogError(std::string msg, std::string &error) {
  if (m_LogLevel <= 2) {
    std::cout << getLogTime() << " [ERROR] " << msg << ": " << error;
  }
}

void Logger::LogWarning(std::string &msg) {
  if (m_LogLevel <= 1) {
    std::cout << getLogTime() << " [WARNING] " << msg;
  }
}

void Logger::LogInfo(std::string &msg) {
  if (m_LogLevel <= 0) {
    std::cout << getLogTime() << " [INFO] " << msg;
  }
}

void PrintGLProgramLog( GLuint program )
{
    //Make sure name is shader
    if( glIsProgram( program ) )
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a program\n", program );
    }
}

void Logger::PrintGLShaderLog(GLuint shader) {

}
