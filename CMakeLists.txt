cmake_minimum_required(VERSION 3.10)
project(TetrisGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thêm thư mục chứa header
include_directories(${CMAKE_SOURCE_DIR}/include)

# Tạo file thực thi và liệt kê tất cả file .cpp
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/game.cpp
    src/grid.cpp
    src/block.cpp
    src/blocks.cpp
    src/colors.cpp
    src/position.cpp
)

# Link với raylib và các thư viện Windows
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
    winmm
    gdi32
    opengl32
    user32
    shell32
)

# Output .exe vào build/bin
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy resource
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Sounds
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Sounds
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Font
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Font
)

# Working directory khi chạy Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
