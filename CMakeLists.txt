cmake_minimum_required(VERSION 3.30)
project(almera)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CORE_LIBS core)

add_library(${CORE_LIBS} core/source/Handler.cpp)
target_include_directories(${CORE_LIBS} PUBLIC core/source)

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} app/source/main.cpp)
target_link_libraries(${PROJECT_NAME} ${CORE_LIBS} ${SDL2_LIBRARIES})
