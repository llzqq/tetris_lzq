cmake_minimum_required(VERSION 3.5)
project(exitedTetris)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/build)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)


include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${SDL3_INCLUDE_DIRS}
)

add_library(
  tetris_lib SHARED
  src/block.cpp
  src/table.cpp
  src/mythread.cpp
  
  )

add_executable(tetris_lzq  src/tetris.cpp)
target_link_libraries(tetris_lzq PRIVATE  tetris_lib pthread)

add_executable(snake  src/snake.cpp)
target_link_libraries(snake PRIVATE SDL3::SDL3)