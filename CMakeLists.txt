cmake_minimum_required(VERSION 3.30)
project(almera VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CORE_LIBS core)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library(${CORE_LIBS} core/source/Handler.cpp)
target_include_directories(${CORE_LIBS} PUBLIC core/source)

find_package(SDL2 REQUIRED)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} app/source/main.cpp)
target_link_libraries(${PROJECT_NAME} ${CORE_LIBS} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
