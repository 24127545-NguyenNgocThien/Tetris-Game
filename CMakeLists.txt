cmake_minimum_required(VERSION 3.10)
project(TetrisGame LANGUAGES CXX)

# Sử dụng C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thêm thư mục chứa file header
include_directories(${CMAKE_SOURCE_DIR}/include)

# Lấy toàn bộ file .cpp trong thư mục src/
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Tạo file thực thi
add_executable(${PROJECT_NAME} ${SOURCES})

# Link với raylib và các thư viện hệ thống trên Windows
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
    winmm
    gdi32
    opengl32
    user32
    shell32
)

# Đặt output .exe và resource vào build/bin
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy resource (Sounds/, Font/) sang build/bin mỗi lần build
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

# Đặt working directory khi chạy trong Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
