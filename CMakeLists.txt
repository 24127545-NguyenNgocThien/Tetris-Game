cmake_minimum_required(VERSION 3.10)

project(Tetris_Game)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories("${CMAKE_SOURCE_DIR}/lib")

file(GLOB SOURCES "src/*.cpp")

add_executable(Tetris_Game ${SOURCES})

set_target_properties(Tetris_Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

target_link_libraries(Tetris_Game raylib opengl32 gdi32 winmm)