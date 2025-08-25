cmake_minimum_required(VERSION 3.10)
project(TetrisGame)

# Dùng C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thêm thư mục header
include_directories(${CMAKE_SOURCE_DIR}/include)

# Lấy toàn bộ file .cpp trong src/
file(GLOB SOURCES "src/*.cpp")

# Tạo file thực thi
add_executable(TetrisGame ${SOURCES})

# Link raylib + thư viện Windows
target_link_libraries(TetrisGame ${CMAKE_SOURCE_DIR}/lib/libraylib.a winmm gdi32 opengl32 user32 shell32)

# Copy resource (Sounds/, Font/) sang thư mục build/bin
file(COPY ${CMAKE_SOURCE_DIR}/Sounds DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CMAKE_SOURCE_DIR}/Font DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Xuất file exe vào build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
